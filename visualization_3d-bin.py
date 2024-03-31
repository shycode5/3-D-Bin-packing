import plotly.graph_objects as go
import random

class Box:
    def _init_(self, length, width, height, xPos, yPos, zPos, index):
        self.length = length
        self.width = width
        self.height = height
        self.xPos = xPos
        self.yPos = yPos
        self.zPos = zPos
        self.index = index

def visualize_packing(packed_boxes, pallet_length, pallet_width, pallet_height):
    fig = go.Figure()

    # Add the packed boxes as 3D cubes with random colors
    for box in packed_boxes:
        color = f"rgb({random.randint(0, 255)}, {random.randint(0, 255)}, {random.randint(0, 255)})"
        fig.add_trace(go.Mesh3d(
            x=[box.xPos, box.xPos + box.length, box.xPos + box.length, box.xPos, box.xPos, box.xPos + box.length, box.xPos + box.length, box.xPos],
            y=[box.yPos, box.yPos, box.yPos + box.width, box.yPos + box.width, box.yPos, box.yPos, box.yPos + box.width, box.yPos + box.width],
            z=[box.zPos, box.zPos, box.zPos, box.zPos, box.zPos + box.height, box.zPos + box.height, box.zPos + box.height, box.zPos + box.height],
            i=[0, 0, 4, 4, 1, 1, 5, 5, 3, 3, 7, 7, 2, 2, 6, 6, 0, 1, 2, 3, 4, 5, 6, 7],
            j=[1, 2, 5, 6, 0, 3, 4, 7, 5, 6, 1, 2, 4, 7, 0, 3, 2, 3, 0, 1, 6, 7, 4, 5],
            k=[3, 0, 7, 4, 2, 5, 6, 1, 1, 0, 3, 2, 7, 4, 5, 6, 6, 7, 2, 3, 0, 1, 4, 5],
            opacity=0.6,
            color=color,
            name=f'Box {box.index}'
        ))

    # Add the pallet as a 3D cube
    fig.add_trace(go.Mesh3d(
        x=[0, pallet_length, pallet_length, 0, 0, pallet_length, pallet_length, 0],
        y=[0, 0, pallet_width, pallet_width, 0, 0, pallet_width, pallet_width],
        z=[0, 0, 0, 0, pallet_height, pallet_height, pallet_height, pallet_height],
        i=[0, 1, 1, 0, 3, 2],
        j=[1, 2, 3, 0, 5, 4],
        k=[3, 0, 1, 2, 4, 5],
        opacity=0.2,
        color='gray',
        name='Pallet'
    ))

    fig.update_layout(
        title='Packed Boxes',
        scene=dict(
            xaxis=dict(title='X'),
            yaxis=dict(title='Y'),
            zaxis=dict(title='Z')
        )
    )

    fig.show()

packed_boxes = [
    Box(52, 60, 42, 30, 21, 26, 0),
    Box(52, 60, 42, 30, 63, 26, 1),
    Box(36, 46, 84, 78, 23, 42, 2),
    Box(26, 36, 84, 73, 64, 42, 3)
]

pallet_length = 104
pallet_width = 97
pallet_height = 84

visualize_packing(packed_boxes, pallet_length, pallet_width, pallet_height)