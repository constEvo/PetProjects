# PetProjects

1. The Grid project, developed in Qt6 and C++, is a showcase of my practical skills in object-oriented programming, readable code design, and efficient use of Qt frameworks. Through this project, I focused on implementing OOP principles to enhance maintainability and readability while managing memory and optimizing performance. The development process was an opportunity to sharpen my C++ expertise and explore advanced features of Qt6, including UI, multimedia and 2D graphics. This project serves both as a technical demonstration and a creative example of my ability to manage complex codebases effectively.

Main goal of the game is getting as high score as possible. You can achieve this goal through collecting databanks, destroying enemy cycles and tanks with projectiles. Game proccess concentrate inside the arena. If player try break trough, he will lost immediately. 

To make gameplay more enjoyable there are some buffs including shield and triple projectile weapon. Shield could help destroy enemy light cycles and absorb tank's projectiles. Triple projectile weapon could annihilate anything on it's way. To add some space for making mistakes there is health count. In case if player received damage, there will be chance to restore health with special pick-ups.

In this projects to move AI characters was used simple A* algorithm, that calculate closet cell to target (either random spot on arena or player). If enemy cycles too close to player, their speed drasticly increases and they start chase player's bike. 

There is volume control in settings menu. It is possible to change music and sound effects volume via volume sliders.

Mapping:
Left arrow - move left
Right arrow - move right
Up arrow - move up
Down arrow - move down
Space key - shoot projectile
Escape key - pause game

Build requirements:
For this project was used QT 6.7.2, that includes next modules: core,gui, multimedia, multimediawidgets, spatialaudio, widgets, with using qmake, and c++ 17.




