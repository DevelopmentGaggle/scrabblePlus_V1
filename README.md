ScrabblePlus
====================

A Scrabble Board Interface For Bridging the Virtual World and the Real World
---------------------

The goal of this project was to design a computer user interface that would auto score a real-world scrabble board.
This requires a user interface (QT Widgets), image processing (OpenCV), and text recognition (Tesseract).
All the user has to do is press a button at the end of each turn, and it will move onto the next turn and auto-score their play.

## Inspiration
Steven and I were thinking of various projects we could work on, and board games kept coming up.
Whether that be Chess, Checkers, several other esoteric board games, or Scrabble, 
we thought they all could all lead to an interesting project.
We ended up choosing Scrabble due to the novelty and the difficulty of the project, 
and ended up regretting it in terms of sleep, but coming out of it with far more knowledge and a working product.

## What it does
The project allows the user to take a picture after each turn of Scrabble (in the same, fixed position above the board).
This picture allows the update of the user interface and the score corresponding to who played that turn.
Additionally, the software allows taking pictures from skewed angles, allowing the possibility of more camera angles after calibration.

## How we built it
After we were able to start working on the project we immediately divided up tasks.
Steven took the lead on the game engine, and I focused on the user interface and asset generation.
Given that my C++ code experience was highly limited before all of this, it was a steep learning curve for QT Widgets.
I had used the QT library in Python for a personal project several months ago, but the syntax was significantly different.
Due to this, Steven was able to finish the game engine before me, handing it to me to integrate with my user interface.
After this he started working on the OpenCV and Tesseract libraries, and got a working class that allowed us to do everything we needed to do.
At this point we then spent the next 4 hours painstakingly going through build errors when we tried to run it on each other's machines, barely making it in time for the submission!

## Challenges we ran into
Integration is a nightmare. We spent a lot of the time during the project just trying to get things to play nice with each other. 
A lot of these problems stemmed from using external libraries that we had to set up during the hackathon, but another large portion 
was just trying to get the same code to run on each other's computers. So, from this, I learned that we both needed to work 
from the same IDE and IDE settings. This nearly resulted in us not being able to finish the project before the end of the competition.

Also, we had a lot of difficultly with the image parsing. Originally it was really finicky and gave a lot of errors, but 
eventually we were able to tune them out. Oddly enough, a lot of this was fixed with a Gaussian blur. 
This was because we were taking the difference between two images to find what changed between those two images.
Small movements between the two photos resulted in sharp lines in the difference image.
This was fixed with the image blur because it eliminated the noise lines that the difference image produced.
Additional image processing was done to make the thresholding image more uniform (clumped by groups).
We then drew a rectangle around this clump, allowing us to select that portion of the image.
Once the image was selected, we could run character recognition to detect characters on the screen.
This was also a finicky process of tuning, but tuning parameters were eventually found after some trial and error.

## Accomplishments that we're proud of
I'm really happy I was able to finish the GUI. I've notoriously taken a very long time to develop these kinds of projects,
and learning how to do it quickly, let alone in a new language, was very gratifying. Additionally, the use of so many external
libraries is also satisfying because most of the projects I've worked on relied on home-brewed classes or the standard library.
Also, when the first image detection worked, it was super cool! It took a lot of time, 
but when it was suddenly able to just look at the board and produce the word that was just added it was something else. 
I've never worked on a project like this, and this has made me more confident in my abilities.

## What's next for ScrabblePlus
There are many features we could add, but I think fine-tuning what we have now will be far better.
While we have something that is mostly working, there are still occasional problems that a better image recognition software could prevent.
As a result, we would probably work on making image detection more robust in a variety of lighting conditions, environments, and image positions.
