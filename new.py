import networkx as nx
import matplotlib.pyplot as plt

# Read edge list from C program output
edge_list = [
    (0, 1),
    (0, 2),
    # Add more edges here...
]

# Create a graph from the edge list
G = nx.Graph()
G.add_edges_from(edge_list)

# Visualize the graph
nx.draw(G, with_labels=True, node_color='skyblue', node_size=800, edge_color='black', linewidths=1, font_size=15)
plt.title('Friendship Network')
plt.show()
