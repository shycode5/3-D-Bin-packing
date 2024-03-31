# 3-D-Bin-packing
**3D Bin Packing Algorithm in C**
This algorithm solves the 3D bin packing problem, which involves efficiently packing a set of three-dimensional objects (boxes) into a limited number of three-dimensional bins (containers) while minimizing wasted space. The algorithm aims to maximize space utilization and optimize the packing arrangement.

**Problem Statement**
• Given a series of boxes ( LxBxH ), write an algorithm to palletize them in the same
• The algorithm can will either choose to place the box on the pallet or skip the box.
• The boxes can only be accessed one at a time.
• The pallet should be in a stable state at any given time.
• Boxes cannot overlap on the pallet.

**Algorithm Overview**
The 3D bin packing algorithm follows these steps to solve the problem:

**Box Placement**: The algorithm iterates over each box and tries all possible orientations and positions within the pallets.

**Overlap Check**: For each position, the algorithm checks if the box overlaps with any previously placed boxes.

**Stability Check**: The algorithm verifies if the box is stable by comparing its volume to the volume of the lower boxes it rests upon.

**Packing Result**: If a valid position is found, the algorithm places the box on top of the pallet.

**Skipping**: If a box cannot be placed in any position, the algorithm skips it.

**Output**: The algorithm outputs the positions of the packed boxes, including the coordinates of their centers.



**Conclusion** : 
The 3D bin packing algorithm implemented in this repository offers a solution to efficiently pack three-dimensional boxes into pallets while maximizing space utilization and ensuring stability. By following the steps outlined in the README file, users can easily understand and use the algorithm to optimize packing arrangements in various scenarios.

