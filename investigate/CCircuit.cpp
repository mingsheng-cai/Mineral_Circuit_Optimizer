#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <omp.h>

#include "circuit/CCircuit.h"

const double k_G_C = 0.004, k_G_I = 0.001;
const double k_w_C = 0.0002, k_w_I = 0.0003;
const double V = 10.0, phi = 0.1, rho = 3000.0;

// Constructor implementation
Circuit::Circuit(int num_units) : numUnits(num_units) {
    this->concentrateG = 0;
    this->tailingsG = 0;
    this->concentrateW = 0;
    this->tailingsW = 0;

    units.resize(numUnits);
}

void Circuit::print_info() const {
    std::cout << "Final Concentrate Gerardium: " << concentrateG << std::endl;
    std::cout << "Final Concentrate Waste: " << concentrateW << std::endl;
    std::cout << "Final Tailings Gerardium: " << tailingsG << std::endl;
    std::cout << "Final Tailings Waste: " << tailingsW << std::endl;
}

void Circuit::connected(int *circuitVector) {
    feed = circuitVector[0];
    for (int i = 0; i < numUnits; ++i) {
        units[i] = new CUnit(circuitVector[3 * i + 1], circuitVector[3 * i + 2], circuitVector[3 * i + 3]);
    }

    // Set pointers based on the connection numbers in circuit_vector
    for (int i = 0; i < numUnits; ++i) {
        int concNum = units[i]->concNum;
        int interNum = units[i]->interNum;
        int tailsNum = units[i]->tailsNum;

        if (concNum < numUnits) {
            units[i]->setConcPtr(units[concNum]);
        }
        if (interNum < numUnits) {
            units[i]->setInterPtr(units[interNum]);
        }
        if (tailsNum < numUnits) {
            units[i]->setTailsPtr(units[tailsNum]);
        }
    }
}

// Destructor implementation
Circuit::~Circuit() {
    for (auto unit: units) {
        delete unit;
    }
}

void Circuit::initialize_feed_rates(double gerardium_, double waste_) {
    units[feed]->setFeedGerardium(gerardium_);
    units[feed]->setFeedWaste(waste_);
    this->wasteFeed = waste_;
    this->gerardiumFeed = gerardium_;
}

void Circuit::reset_new_feeds() {
    for (auto &unit: units) {
        unit->setNewFeedGerardium(0.0);
        unit->setNewFeedWaste(0.0);
    }
}

void Circuit::calculate_flows(bool parallel = false) {
    if(parallel) {

    reset_new_feeds();
    units[feed]->setNewFeedGerardium(gerardiumFeed);
    units[feed]->setNewFeedWaste(wasteFeed);
    concentrateG = 0;
    concentrateW = 0;
    tailingsG = 0;
    tailingsW = 0;

    double C_G, I_G, T_G, C_w, I_w, T_w;
    C_G = I_G = T_G = C_w = I_w = T_w = 0;

    #pragma omp parallel for reduction(+:concentrateG, concentrateW, tailingsG, tailingsW) private(C_G, I_G, T_G, C_w, I_w, T_w)
    for (auto &unit: units) {
        double total_feed = unit->getFeedGerardium() + unit->getFeedWaste();

        if (total_feed < 1e-14) {
            C_G = I_G = T_G = C_w = I_w = T_w = 0;
            continue;
        }

        double tau = phi * V / (total_feed / rho);
        double R_G_C = k_G_C * tau / (1 + k_G_C * tau + k_G_I * tau);
        double R_G_I = k_G_I * tau / (1 + k_G_C * tau + k_G_I * tau);
        double R_w_C = k_w_C * tau / (1 + k_w_C * tau + k_w_I * tau);
        double R_w_I = k_w_I * tau / (1 + k_w_C * tau + k_w_I * tau);

        C_G = unit->getFeedGerardium() * R_G_C;
        I_G = unit->getFeedGerardium() * R_G_I;
        T_G = unit->getFeedGerardium() * (1 - R_G_C - R_G_I);

        C_w = unit->getFeedWaste() * R_w_C;
        I_w = unit->getFeedWaste() * R_w_I;
        T_w = unit->getFeedWaste() * (1 - R_w_C - R_w_I);

        if (unit->concNum < numUnits) {
            #pragma omp critical
            {
            unit->getConcPtr()->setNewFeedGerardium(unit->getConcPtr()->getNewFeedGerardium() + C_G);
            unit->getConcPtr()->setNewFeedWaste(unit->getConcPtr()->getNewFeedWaste() + C_w);
            }
        } else if (unit->concNum == numUnits) {
            concentrateG += C_G;
            concentrateW += C_w;
        } else if (unit->concNum > numUnits) {
            tailingsG += C_G;
            tailingsW += C_w;
        }

        if (unit->interNum < numUnits) {
            #pragma omp critical
            {
            unit->getInterPtr()->setNewFeedGerardium(unit->getInterPtr()->getNewFeedGerardium() + I_G);
            unit->getInterPtr()->setNewFeedWaste(unit->getInterPtr()->getNewFeedWaste() + I_w);
            }
        } else if (unit->interNum == numUnits) {
            concentrateG += I_G;
            concentrateW += I_w;
        } else if (unit->interNum > numUnits) {
            tailingsG += I_G;
            tailingsW += I_w;
        }

        if (unit->tailsNum < numUnits) {
            #pragma omp critical
            {
            unit->getTailsPtr()->setNewFeedGerardium(unit->getTailsPtr()->getNewFeedGerardium() + T_G);
            unit->getTailsPtr()->setNewFeedWaste(unit->getTailsPtr()->getNewFeedWaste() + T_w);
            }
        }  else if (unit->tailsNum == numUnits) {
            concentrateG += T_G;
            concentrateW += T_w;
        } else if (unit->tailsNum > numUnits) {
            tailingsG += T_G;
            tailingsW += T_w;
        }
    }

    #pragma omp parallel for
    for (auto &unit: units) {
        unit->setDifference();
        unit->setFeedGerardium(unit->getNewFeedGerardium());
        unit->setFeedWaste(unit->getNewFeedWaste());
    }

    }else {
        
    reset_new_feeds();
    units[feed]->setNewFeedGerardium(gerardiumFeed);
    units[feed]->setNewFeedWaste(wasteFeed);
    concentrateG = 0;
    concentrateW = 0;
    tailingsG = 0;
    tailingsW = 0;

    double C_G, I_G, T_G, C_w, I_w, T_w;
    C_G = I_G = T_G = C_w = I_w = T_w = 0;

    for (auto &unit: units) {
        double total_feed = unit->getFeedGerardium() + unit->getFeedWaste();

        if (total_feed < 1e-14) {
            C_G = I_G = T_G = C_w = I_w = T_w = 0;
            continue;
        }

        double tau = phi * V / (total_feed / rho);
        double R_G_C = k_G_C * tau / (1 + k_G_C * tau + k_G_I * tau);
        double R_G_I = k_G_I * tau / (1 + k_G_C * tau + k_G_I * tau);
        double R_w_C = k_w_C * tau / (1 + k_w_C * tau + k_w_I * tau);
        double R_w_I = k_w_I * tau / (1 + k_w_C * tau + k_w_I * tau);

        C_G = unit->getFeedGerardium() * R_G_C;
        I_G = unit->getFeedGerardium() * R_G_I;
        T_G = unit->getFeedGerardium() * (1 - R_G_C - R_G_I);

        C_w = unit->getFeedWaste() * R_w_C;
        I_w = unit->getFeedWaste() * R_w_I;
        T_w = unit->getFeedWaste() * (1 - R_w_C - R_w_I);

        if (unit->concNum < numUnits) {
            unit->getConcPtr()->setNewFeedGerardium(unit->getConcPtr()->getNewFeedGerardium() + C_G);
            unit->getConcPtr()->setNewFeedWaste(unit->getConcPtr()->getNewFeedWaste() + C_w);
        } else if (unit->concNum == numUnits) {
            concentrateG += C_G;
            concentrateW += C_w;
        } else if (unit->concNum > numUnits) {
            tailingsG += C_G;
            tailingsW += C_w;
        }

        if (unit->interNum < numUnits) {
            unit->getInterPtr()->setNewFeedGerardium(unit->getInterPtr()->getNewFeedGerardium() + I_G);
            unit->getInterPtr()->setNewFeedWaste(unit->getInterPtr()->getNewFeedWaste() + I_w);
        } else if (unit->interNum == numUnits) {
            concentrateG += I_G;
            concentrateW += I_w;
        } else if (unit->interNum > numUnits) {
            tailingsG += I_G;
            tailingsW += I_w;
        }

        if (unit->tailsNum < numUnits) {
            unit->getTailsPtr()->setNewFeedGerardium(unit->getTailsPtr()->getNewFeedGerardium() + T_G);
            unit->getTailsPtr()->setNewFeedWaste(unit->getTailsPtr()->getNewFeedWaste() + T_w);
        }  else if (unit->tailsNum == numUnits) {
            concentrateG += T_G;
            concentrateW += T_w;
        } else if (unit->tailsNum > numUnits) {
            tailingsG += T_G;
            tailingsW += T_w;
        }
    }

    for (auto &unit: units) {
        unit->setDifference();
        unit->setFeedGerardium(unit->getNewFeedGerardium());
        unit->setFeedWaste(unit->getNewFeedWaste());
    }
    }
}

bool Circuit::check_convergence(double threshold = 1e-6) {
    for (const auto &unit: units) {
        if (unit->getDifferenceW() > threshold || unit->getDifferenceG() > threshold) {
            return false;
        }
    }
    return true;
}

bool Circuit::Check_Validity(int vector_size, int *circuit_vector) {
    bool check[3] = {false, false, false};
    std::vector<CUnit *> units(vector_size / 3);

    // Checks the first element (feed) is not negative or greater than the number of units
    int feed_id = circuit_vector[0];
    if (feed_id < 0 || feed_id >= vector_size / 3 - 1) {
        return false;
    }

    // Checks the size of vector is equal to the max element * 3 + 1
    if ((*std::max_element(circuit_vector, circuit_vector + vector_size) - 1) * 3 + 1 != vector_size) {
        return false;
    }

    units.clear();
    units.resize(vector_size / 3);

    // Checks format of the circuit vector
    for (int i = 0; i < units.size(); i++) {
        units[i] = new CUnit(circuit_vector[3 * i + 1], circuit_vector[3 * i + 2], circuit_vector[3 * i + 3]);
        // units[i]->mark = false;
        units[i]->setMarked(false);
    }

    if (units.size() == 1)
        return false; // intermediate does not have an outlet and you can't self-recycle, therefore, you cannot have only one unit

    int tail_id = *std::max_element(circuit_vector, circuit_vector + vector_size);
    int conc_id = tail_id - 1;

    Circuit circuit(0);  // Dummy object to call mark_units
    circuit.mark_units(feed_id, units, check);
    // mark_units(feed_id, units, check);

    // Check if there is a path from feed to the outlets
    if (!check[0] || !check[2]) {
        return false;
    }

    for (int id = 0; id < units.size(); id++) {
        // Check if the destinations are negative
        if (units[id]->concNum < 0 || units[id]->interNum < 0 || units[id]->tailsNum < 0) {
            return false;
        }

        // Check if the destinations are greater than the number of units
        if (units[id]->concNum > units.size() + 1 || units[id]->interNum > units.size() + 1 ||
            units[id]->tailsNum > units.size() + 1) {
            return false;
        }

        // Check that the destination is not itself
        if (units[id]->concNum == id || units[id]->interNum == id || units[id]->tailsNum == id) {
            return false;
        }

        // Check for incorrect destination outlet (conc and tail)
        if (units[id]->concNum == units.size() + 1 || units[id]->tailsNum == units.size()) {
            return false;
        }

        // feed number cannot have the same number as the outlets (units or units +1)
        if (circuit_vector[0] == units.size() || circuit_vector[0] == units.size() + 1) {
            return false;
        }

        // Check if the unit has been seen (accessible from feed)
        if (!units[id]->isMarked()) {
            return false;
        }

        // Check if conc and tail stream go to different units
        if (units[id]->concNum == units[id]->tailsNum) {
            return false;
        }
    }

    return true;
}

void Circuit::mark_units(int unit_num, std::vector<CUnit *> &units, bool check[3]) {
    if (units[unit_num]->isMarked()) return;

    // units[unit_num]->mark = true;
    units[unit_num]->setMarked(true);

    // If we have seen this unit already exit
    // Mark that we have now seen the unit

    // If conc_num does not point at a circuit outlet recursively call the function
    if (units[unit_num]->concNum < units.size()) {
        mark_units(units[unit_num]->concNum, units, check);
    } else {
        // ...Potentially do something to indicate that you have seen an exit
        check[0] = true;
    }

    // If inter_num does not point at a circuit outlet recursively call the function
    if (units[unit_num]->interNum < units.size()) {
        mark_units(units[unit_num]->interNum, units, check);
    } else {
        // ...Potentially do something to indicate that you have seen an exit
        check[1] = true;
    }

    // If tails_num does not point at a circuit outlet recursively call the function
    if (units[unit_num]->tailsNum < units.size()) {
        mark_units(units[unit_num]->tailsNum, units, check);
    } else {
        // ...Potentially do something to indicate that you have seen an exit
        check[2] = true;
    }
}
