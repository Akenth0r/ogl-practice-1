# ogl-pratice-1
Simple project for ogl learning

<h1> What's used </h1>
<ul>
  <li> VBO's </li>
  <li> EBO's </li>
  <li> FPS counter </li>
  <li> PathFinding (Lee algorithm) </li>
  <li> OGL 1.1 lighting system </li>
  <li> Mesh loader (wavefront obj) </li>
  <li> Camera transformations (Own camera class was implemented) </li>
  <li> Material loader (using rapidJSON) </li>
  <li> Main program was separated into 3 modules (Display, simulation, data) </li>
  <li> Moving depending on camera orientation </li>
  <li> Passability map </li>
  <li> Simple collision (player can move yellow boxes) </li>

</ul>

<h1> Controls </h1>
<ul>
  <li> <kbd>LMB + drag</kbd> - camera rotation </li>
  <li> <kbd> Mouse Scroll </kbd> - zoom in\out </li>
  <li> <kbd> WASD </kbd> - player moving </li>
  <li> <kbd> E </kbd> - automove to upper right corner of the map (if it's impossible to move there, finds the nearest cell and moves to it)
</ul>

<h2> PathFinder example </h2>
![](https://github.com/Akenth0r/ogl-practice-1/blob/master/pathfinder.gif?raw=true)
