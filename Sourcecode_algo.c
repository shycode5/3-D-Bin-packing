#include <stdio.h>

typedef struct {
    int length;
    int width;
    int height;
    int xPos;
    int yPos;
    int zPos;
    int index;
} Box;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int calculateOverlapArea(Box box1, Box box2) {
    int xOverlap = max(0, min(box1.xPos + box1.length, box2.xPos + box2.length) - max(box1.xPos, box2.xPos));
    int yOverlap = max(0, min(box1.yPos + box1.width, box2.yPos + box2.width) - max(box1.yPos, box2.yPos));
    int zOverlap = max(0, min(box1.zPos + box1.height, box2.zPos + box2.height) - max(box1.zPos, box2.zPos));
    return xOverlap * yOverlap * zOverlap;
}

int canFit(Box box, int xPos, int yPos, int zPos, Box* boxes, int numPackedBoxes) {
    for (int j = 0; j < numPackedBoxes; j++) {
        int boxIndex = boxes[j].index;
        int boxXEnd = boxes[boxIndex].xPos + boxes[boxIndex].length;
        int boxYEnd = boxes[boxIndex].yPos + boxes[boxIndex].width;
        int boxZEnd = boxes[boxIndex].zPos + boxes[boxIndex].height;

        if (!(xPos >= boxXEnd || box.xPos >= boxXEnd ||
              yPos >= boxYEnd || box.yPos >= boxYEnd ||
              zPos >= boxZEnd || box.zPos >= boxZEnd)) {
            return 0; // Overlapping with a previously placed box
        }
    }
    return 1; // Box can fit without overlapping
}

int isStable(Box box, Box* packedBoxes, int numPackedBoxes) {
    for (int i = 0; i < numPackedBoxes; i++) {
        Box lowerBox = packedBoxes[i];
        int lowerBoxXEnd = lowerBox.xPos + lowerBox.length;
        int lowerBoxYEnd = lowerBox.yPos + lowerBox.width;
        int lowerBoxZEnd = lowerBox.zPos + lowerBox.height;

        if (box.xPos >= lowerBox.xPos && box.xPos + box.length <= lowerBoxXEnd &&
            box.yPos >= lowerBox.yPos && box.yPos + box.width <= lowerBoxYEnd &&
            box.zPos >= lowerBox.zPos && box.zPos + box.height <= lowerBoxZEnd) {
            int boxVolume = box.length * box.width * box.height;
            int lowerBoxVolume = lowerBox.length * lowerBox.width * lowerBox.height;
            if (boxVolume < 0.5 * lowerBoxVolume) {
                return 0; // Box is not stable
            }
        }
    }
    return 1; // Box is stable
}

int main() {
    int palletLength = 104;
    int palletWidth = 97;
    int palletHeight = 84;

    Box pallet;
    pallet.length = palletLength;
    pallet.width = palletWidth;
    pallet.height = palletHeight;
    pallet.xPos = 0;
    pallet.yPos = 0;
    pallet.zPos = 0;

    Box boxes[] = {
        {52, 60, 42, 0, 0, 0, 0},
        {52, 60, 42, 0, 0, 0, 1},
        {36, 46, 84, 0, 0, 0, 2},
        {26, 36, 84, 0, 0, 0, 3},
        {25, 20, 25, 0, 0, 0, 4},
        {26, 36, 21, 0, 0, 0, 5},
        {26, 36, 21, 0, 0, 0, 6},
        {26, 36, 21, 0, 0, 0, 7},
        {26, 36, 21, 0, 0, 0, 8},
        {8, 20, 21, 0, 0, 0, 9},
        {8, 20, 21, 0, 0, 0, 10},
        {8, 20, 21, 0, 0, 0, 11},
        {8, 20, 21, 0, 0, 0, 12},
        {8, 20, 21, 0, 0, 0, 13},
        {8, 20, 21, 0, 0, 0, 14}
    };

    int numBoxes = sizeof(boxes) / sizeof(Box);

    Box packedBoxes[numBoxes];
    int numPackedBoxes = 0;

    for (int i = 0; i < numBoxes; i++) {
        Box box = boxes[i];
        int stacked = 0;

        // Try all possible orientations of the box
        for (int orientation = 0; orientation < 3; orientation++) {
            int temp = box.length;
            box.length = box.width;
            box.width = box.height;
            box.height = temp;

            // Try all possible positions within the pallet
            for (int xPos = 0; xPos <= palletLength - box.length; xPos++) {
                for (int yPos = 0; yPos <= palletWidth - box.width; yPos++) {
                    for (int zPos = 0; zPos <= palletHeight - box.height; zPos++) {
                        if (canFit(box, xPos, yPos, zPos, packedBoxes, numPackedBoxes) &&
                            isStable(box, packedBoxes, numPackedBoxes)) {
                            // Stack the box on top of the pallet
                            box.xPos = xPos;
                            box.yPos = yPos;
                            box.zPos = zPos;
                            box.index = i;
                            packedBoxes[numPackedBoxes++] = box;
                            stacked = 1;
                            break;
                        }
                    }
                    if (stacked) {
                        break;
                    }
                }
                if (stacked) {
                    break;
                }
            }
            if (stacked) {
                break;
            }
        }

        if (!stacked) {
            printf("skip\n");
        }
    }

    for (int i = 0; i < numPackedBoxes; i++) {
        Box box = packedBoxes[i];
        int centerX = box.xPos + box.length / 2;
        int centerY = box.yPos + box.width / 2;
        int centerZ = box.zPos + box.height / 2;
        printf("Box %d: Position (%d, %d, %d)\n", box.index, centerX, centerY, centerZ);
    }
}