import graphviz
import matplotlib.pyplot as plt
import argparse
import pandas as pd


# Function to parse a string into a list of integers
def parse_list(string):
    # Remove any surrounding brackets and split the string by commas
    items = string.strip('[]').split(',')
    return [int(item) for item in items]


# Initialize the argument parser
parser = argparse.ArgumentParser(description='Command line arguments for \
                                 visualizing the circuit diagram.')

# Add the arguments
parser.add_argument('vector', type=parse_list)
parser.add_argument('perf', type=float)
parser.add_argument('recovery', type=float)
parser.add_argument('grade', type=float)

# Parse the arguments
args = parser.parse_args()
x = args.vector
p = args.perf
r = args.recovery
g = args.grade

# Create Digraph object
graph = graphviz.Digraph()
graph.attr(rankdir='LR', nodesep='0.7', ranksep='0.7', splines='ortho',
           overlap='false', dpi='300')

# Define the nodes
feed_node = 'Feed'
concentrate = 'Concentrate'
tailings = 'Tailings'

# Add common nodes to the graph
graph.node(feed_node, shape='box')
graph.node(concentrate, shape='box')
graph.node(tailings, shape='box')

# Add edges from feed node to the first unit
graph.edge(feed_node, f'Unit {x[0]}', color='black')

num_nodes = (len(x) - 1) // 3  # Excluding Concentrate and Tailings

# Add edges between units
for i in range(len(x) - 1):
    # Get the from node
    from_node = f'Unit {i // 3}'
    # Get the to node
    to_node = concentrate if x[i + 1] == (num_nodes) else tailings \
        if x[i + 1] == (num_nodes + 1) else f'Unit {x[i + 1]}'
    # Colour based on output stream
    color = 'blue' if i % 3 == 0 else 'purple' if i % 3 == 1 else 'red'
    graph.edge(from_node, to_node, color=color)

# Render the graph
graph.render('../circuit_diagrams/circuit', cleanup=True, format='png',
             view=False)

# Create legend using Matplotlib
legend_labels = {'Concentrate': 'blue', 'Intermediate': 'purple',
                 'Tailings': 'red'}
legend_handles = [plt.Line2D([0], [0], marker='o', color='w', markersize=5,
                             markerfacecolor=color, label=label)
                  for label, color in legend_labels.items()]

# Create column names
columns = ['Feed'] + [f'Unit {i}' for i in range(0, num_nodes)]

# Reshape the input list to match the desired table format
reshaped_list = [[x[0]]] + [[' '.join(map(str, x[i:i + 3]))]
                            for i in range(1, len(x), 3)]

# Create a DataFrame
df = pd.DataFrame(reshaped_list).transpose()
df.columns = columns

# Plot the legend and table on the same figure
plt.figure(figsize=(20, 15))

# Show the Graphviz plot, legend and vector as a table
plt.subplot(1, 2, 1)
plt.imshow(plt.imread('../circuit_diagrams/circuit.png'))
plt.legend(handles=legend_handles, labels=legend_labels.keys(),
           loc='center left', bbox_to_anchor=(1, 0.5), fontsize='small')
plt.table(cellText=df.values, colLabels=df.columns, loc='top',
          cellLoc='center', fontsize='small', bbox=[0.25, 1.2, 0.5, 0.2])
plt.axis('off')

# Display the performance metrics of the circuit
plt.text(0.5, 1.15, f'Performance: {p}', ha='center', va='top', fontsize=8,
         transform=plt.gca().transAxes)
plt.text(0.5, 1.1, f'Recovery: {r * 100}%', ha='center', va='top', fontsize=8,
         transform=plt.gca().transAxes)
plt.text(0.5, 1.05, f'Grade: {g * 100}%', ha='center', va='top', fontsize=8,
         transform=plt.gca().transAxes)

# Save the plot
plt.savefig('../circuit_diagrams/circuit.png', bbox_inches='tight')
