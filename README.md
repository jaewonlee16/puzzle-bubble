# Puzzle Bubble Project
Final Project of Program Methology in 2020 Spring

## Project Overview
The Puzzle Bubble project is a game development assignment where students create a bubble shooter game. This README provides an overview of the project specifications, rules, algorithms, and submission details.

## Environment
- This project is built on visual studio.
- The OpenGL Library glut32.dll should be downloaded.

## Game Specifications

### Start Condition
- The start bubble is placed on the bubble shooter.
- The next bubble is displayed near the start bubble.
- There are at least 4 different bubble colors.

### Defeat Condition
- The game ends if any bubble reaches the lower boundary.

### Gameplay Mechanics
1. **Bubble Shooter Rotation:**
   - The bubble shooter can rotate between 10° and 170°.
   - The shooter does not shoot horizontally or downward.
  
2. **Bubble Shooting:**
   - The bubble moves in the direction pointed by the shooter.
   - If time runs out before shooting, the bubble is automatically shot.

3. **Collision Handling:**
   - If the bubble hits the left/right boundary, it bounces off.
   - The bubble stops when it reaches the upper boundary or collides with another bubble.
   - If at least 3 bubbles of the same color are connected, they are removed, and hanging bubbles fall down.

### Algorithms

#### Remove Algorithm
- Uses recursion to remove connected bubbles of the same color.

#### Drop Algorithm
- Uses recursion to identify and drop bubbles that are no longer connected to the top after a removal.


## References
- Exemplar game: [Puzzle Bobble](https://www.shooter-bubble.com/puzzle-bobble.php)
- OpenGL configuration for converting screen coordinates is provided for reference.

For any questions or further clarifications, please contact the project coordinator.

---

This README provides the necessary information to understand and complete the Puzzle Bubble project. Follow the specifications and guidelines closely to ensure your project meets the requirements and achieves the highest possible score.
