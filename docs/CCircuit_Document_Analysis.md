# Optimised Circuit Configuration vs Economic Factors

## Introduction
To get a heuristic circuit design we utilised our base case solution and varied 3 economic factors (Number of units in the circuit, Price paid per gerardium relative to waste, Purity of the input feed) independently to observe how the optimal circuit configuration changes with each factor. This allows us to identify common patterns in the optimal circuit.


## Base Case (10 Units with Specified Economic Factors)
From the base case circuit solution, we observed several features:

1. A row of units which handles further filtering of the tail streams. (Units 5, 0, 4, 7, 3)
2. A unit which takes in the concentrate streams from the row of units. (Unit 1)
3. A unit to handle one last filtering of the material before sending to the concentrate (Unit 8)
4. A unit which takes in the intermediate streams from this row of units, and recycles its tailing to the start of the tail stream unit row and directs its concentrate stream towards the concentrate unit (Unit 6)
5. A unit which allows recycling of material midway through the circuit (Unit 9)

![alt text](https://raw.githubusercontent.com/acse-sc4623/img/main/circuit_unit9.png)

## Economic Factors:
### 1) Number of Units
Investigated circuits with a number of units from 5 to 15:

There are common features among the optimal configuration of circuits with a different number of units
-  The concentrate and tailing streams are connected to only one other unit each
- Overall they have a similar structure to the base case as described above, these features includes:
    - A row of units to handle the tailing streams (This row is longer and more obvious as number of units increase)
    - 1 unit which handles the intermediate streams of these units
    - 1 unit which handles the concentrate stream of these units
- Circuits with more units, have units to handle recycling and further filtering between these structures, as seen in the base case and the circuit with 15 units below (2 units, Unit 6, 7,  handles filtering before depositing in concentrate)

**Circuit with 5 units:**
![alt text](https://raw.githubusercontent.com/acse-sc4623/img/main/circuit_unit5.png)

**Circuit with 15 units:**
![alt text](https://raw.githubusercontent.com/acse-sc4623/img/main/circuit_unit15.png)

### 2) Price of Reward and Penalty
Investigated 4 different cases utilising circuits of 5 units, 10 units: 
1. Reward of £100 * 5 per kg
2. Reward of £100 * 10 per kg
3. Penalties of £750 * 5 per kg
4. Penalties of £750 * 10 per kg

With 5 units:
- At higher penalty, the optimal circuit’s intermediate streams showed tendency to recycle (Unit 3, 4, 6 conducts further filtering), following the route of the tail stream, as opposed to continuing forward in the circuit towards the concentrate

![alt text](https://raw.githubusercontent.com/acse-sc4623/img/main/circuit_unit5_1.png)

- For higher rewards, the circuit is comparable to the base case for 5 units, just with an additional unit to filter for the tailing stream (to extract as much value from this stream)

![alt text](https://raw.githubusercontent.com/acse-sc4623/img/main/circuit_unit5_2.png)

With 10 units:
- The same general structure mentioned multiple times above was observed for various degrees of penalities and rewards
- A similar trend to the circuit of 5 units was observed 
- For higher rewards, there are more filters for tailing stream:

**£1000 reward, 10 units circuit**
<img src="https://raw.githubusercontent.com/acse-sc4623/img/main/circuit_unit10.png" alt="alt text" style="zoom: 25%;" />

- For a high penalty there is an increased number of units to filter out the material before depositing into the concentrate (Units 8, 4, 3), and fewer units to filter out tailing stream 
- This is expected as we want to prevent as much waste in the concentrate as possible, therefore prioritise this over collecting material from tailing stream

**£7500 penalty, 10 units circuit**
<img src="https://raw.githubusercontent.com/acse-sc4623/img/main/circuit_unit10_1.png" alt="alt text" style="zoom: 25%;" />

### 3) Purity
Investigated a range of gerardium feed purity, from 10-90%:

- There was a general trend where an increase in purity of gerardium corresponded to more intermediate flow streams directly connected to the concentrate.
    -  For an extreme case of 90% geranium and 10% waste for a circuit of 5 units it connects all unit's concentrate and intermediate streams directly to the concentrate.

**90% gerardium feed, 5 units circuit:**
![alt text](https://raw.githubusercontent.com/acse-sc4623/img/main/circuit_unit5_3.png)

**90% gerardium feed, 10 units circuit:**
- A similar trend, to a lesser degree, can be seen in the 10 units circuit, where earlier on in the row of units (Units 0, 8, 7) the intermediate streams directly connect to the concentrate, but later on in the row (with increasing waste content) the intermediate streams is recycled to the start of the tailing row. Note that there is no unit designated for recycling like in the base case.
<img src="https://raw.githubusercontent.com/acse-sc4623/img/main/circuit_unit10_2.png" alt="alt text" style="zoom: 25%;" /> 

- Overall the general design for having a row of units to filter out the tailing stream holds true for the range of purities explored.
- The circuit design differs at lower purities where it is closer to the base case with fewer units in a row and units utilised for further filtering prior to deposition to the concentrate.

## Heuritic Circuit Design

Based on the above observations we can see some similarities in the design which could provide an insight into a heuristic circuit design to consider:

1. Having a row of units to filter out the tailing streams leading to the tail.
2. A unit to handle concentrate streams from this row of units.
3. Given sufficient units, the intermediate streams from these rows will be fed into another unit before either being sent to the concentrate unit/recycled to the top of the row of units

Additional Considerations:

4. Depending on the penalty cost, we can also arrange more units (if higher penalty) or less units (if lower penalty) before material reaches concentrate unit to further filter out the waste material from concentrate
5. Purity can also be taken into consideration when optimising a circuit. We can arrange more units for the tailing stream row (to extract as much valuable material from waste before deposal) the more pure the feed, the more units we can assign for this purpose
