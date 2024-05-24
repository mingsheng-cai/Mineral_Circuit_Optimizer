/**
 * @file CUnit.h
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

#pragma once

#ifndef CIRCUIT_MODELLING_CUNIT_H
#define CIRCUIT_MODELLING_CUNIT_H

#include <memory> // 包含内存头文件
#include <cmath>

class CUnit {
public:
    /**
     * @brief Default constructor for CUnit.
     *
     * Constructs a CUnit object with default values for concentrate, intermediate, and tailings numbers.
     */
    CUnit();

    /**
     * @brief Parameterized constructor for CUnit.
     *
     * Constructs a CUnit object with specified values for concentrate, intermediate, and tailings numbers.
     *
     * @param concNum The concentrate number.
     * @param interNum The intermediate number.
     * @param tailsNum The tailings number.
     */
    CUnit(int concNum, int interNum, int tailsNum);

    int concNum; /**< The concentrate number */
    int interNum; /**< The intermediate number */
    int tailsNum; /**< The tailings number */

    /**
     * @brief Checks if the unit is marked.
     *
     * @return True if the unit is marked, otherwise false.
     */
    bool isMarked() const;

    /**
     * @brief Sets the mark status of the unit.
     *
     * @param mark The mark status to set.
     */
    void setMarked(bool mark);

    /**
     * @brief Gets the feed rate of gerardium.
     *
     * @return The feed rate of gerardium.
     */
    double getFeedGerardium() const;

    /**
     * @brief Sets the feed rate of gerardium.
     *
     * @param feedGerardium The feed rate of gerardium to set.
     */
    void setFeedGerardium(double feedGerardium);

    /**
     * @brief Gets the feed rate of waste.
     *
     * @return The feed rate of waste.
     */
    double getFeedWaste() const;

    /**
     * @brief Sets the feed rate of waste.
     *
     * @param feedWaste The feed rate of waste to set.
     */
    void setFeedWaste(double feedWaste);

    /**
     * @brief Gets the new feed rate of gerardium.
     *
     * @return The new feed rate of gerardium.
     */
    double getNewFeedGerardium() const;

    /**
     * @brief Sets the new feed rate of gerardium.
     *
     * @param newFeedGerardium The new feed rate of gerardium to set.
     */
    void setNewFeedGerardium(double newFeedGerardium);

    /**
     * @brief Gets the new feed rate of waste.
     *
     * @return The new feed rate of waste.
     */
    double getNewFeedWaste() const;

    /**
     * @brief Sets the new feed rate of waste.
     *
     * @param newFeedWaste The new feed rate of waste to set.
     */
    void setNewFeedWaste(double newFeedWaste);

    /**
     * @brief Gets the difference in feed rate of gerardium.
     *
     * @return The difference in feed rate of gerardium.
     */
    double getDifferenceG() const;

    /**
     * @brief Gets the difference in feed rate of waste.
     *
     * @return The difference in feed rate of waste.
     */
    double getDifferenceW() const;

    /**
     * @brief Sets the differences in feed rates for gerardium and waste.
     */
    void setDifference();


    /**
     * @brief Gets the pointer to the concentrate connection.
     *
     * @return The pointer to the concentrate connection.
     */
    CUnit *getConcPtr() const;

    /**
     * @brief Sets the pointer to the concentrate connection.
     *
     * @param ptr The pointer to the concentrate connection to set.
     */
    void setConcPtr(CUnit *ptr);

    /**
     * @brief Gets the pointer to the intermediate connection.
     *
     * @return The pointer to the intermediate connection.
     */
    CUnit *getInterPtr() const;

    /**
     * @brief Sets the pointer to the intermediate connection.
     *
     * @param ptr The pointer to the intermediate connection to set.
     */
    void setInterPtr(CUnit *ptr);

    /**
     * @brief Gets the pointer to the tailings connection.
     *
     * @return The pointer to the tailings connection.
     */
    CUnit *getTailsPtr() const;

    /**
     * @brief Sets the pointer to the tailings connection.
     *
     * @param ptr The pointer to the tailings connection to set.
     */
    void setTailsPtr(CUnit *ptr);

private:
    bool mark; /**< Mark status of the unit */
    double feedGerardium; /**< Feed rate of gerardium */
    double feedWaste; /**< Feed rate of waste */
    double newFeedGerardium; /**< New feed rate of gerardium */
    double newFeedWaste; /**< New feed rate of waste */
    double differenceG; /**< Difference in feed rate of gerardium */
    double differenceW; /**< Difference in feed rate of waste */

    CUnit *concPtr; /**< Pointer to the concentrate connection */
    CUnit *interPtr; /**< Pointer to the intermediate connection */
    CUnit *tailsPtr; /**< Pointer to the tailings connection */
};

#endif // CIRCUIT_MODELLING_CUNIT_H
