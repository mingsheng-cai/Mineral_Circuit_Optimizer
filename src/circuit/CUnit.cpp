/**
 * @file CUnit.cpp
 *
 * @brief Defines the CUnit class for representing a unit within a circuit system.
 *
 * The CUnit class provides methods to manage and simulate individual units within a circuit. It includes methods
 * for setting and getting various properties of the unit, such as feed rates, mark status, and connection pointers.
 * This class is designed to facilitate the modeling and simulation of circuits in various applications, including
 * industrial processes and scientific research.
 *
 * @date Created on May 20, 2024
 *
 * @authors
 * ACS Gerardium Rush - Pentlandite:
 *   - Alex N Njeumi
 *   - Geyu Ji
 *   - Melissa Y S Sim
 *   - Mingsheng Cai
 *   - Peifeng Tan
 *   - Yongwen Chen
 *   - Zihan Li
 */

#include "circuit/CUnit.h"

// Default Constructor
CUnit::CUnit()
        : concNum(-1), interNum(-1), tailsNum(-1),
          mark(false), feedGerardium(1e-6), feedWaste(1e-6),
          newFeedGerardium(0.0), newFeedWaste(0.0), differenceW(1.0), differenceG(1.0) {}

// Parameterized Constructor
CUnit::CUnit(int conc_num, int inter_num, int tails_num)
        : concNum(conc_num), interNum(inter_num), tailsNum(tails_num),
          mark(false), feedGerardium(1e-6), feedWaste(1e-6),
          newFeedGerardium(0.0), newFeedWaste(0.0), differenceW(1.0), differenceG(1.0) {}

bool CUnit::isMarked() const { return mark; }

void CUnit::setMarked(bool mark) { this->mark = mark; }

double CUnit::getFeedGerardium() const { return feedGerardium; }

void CUnit::setFeedGerardium(double feed_gerardium) { this->feedGerardium = feed_gerardium; }

double CUnit::getFeedWaste() const { return feedWaste; }

void CUnit::setFeedWaste(double feed_waste) { this->feedWaste = feed_waste; }

double CUnit::getDifferenceG() const { return differenceG; }

double CUnit::getDifferenceW() const { return differenceW; }

void CUnit::setDifference() {
    differenceG = std::abs(newFeedGerardium - feedGerardium) / feedGerardium;
    differenceW = std::abs(newFeedWaste - feedWaste) / feedWaste;
}

double CUnit::getNewFeedGerardium() const { return newFeedGerardium; }

void CUnit::setNewFeedGerardium(double newFeedGerardium) { this->newFeedGerardium = newFeedGerardium; }

double CUnit::getNewFeedWaste() const { return newFeedWaste; }

void CUnit::setNewFeedWaste(double newFeedWaste) { this->newFeedWaste = newFeedWaste; }

CUnit *CUnit::getConcPtr() const { return concPtr; }

void CUnit::setConcPtr(CUnit *ptr) { concPtr = ptr; }

CUnit *CUnit::getInterPtr() const { return interPtr; }

void CUnit::setInterPtr(CUnit *ptr) { interPtr = ptr; }

CUnit *CUnit::getTailsPtr() const { return tailsPtr; }

void CUnit::setTailsPtr(CUnit *ptr) { tailsPtr = ptr; }
