# life-game
<h3>Simple console C++ implementation of the famous Game of Life.</h1>
There are some details though:
<ul>
  <li>each cell has a life level - amount of times it was alive in a row;</li>
  <li>a cell cannot be alive more than 12 times in a row - it's life level will de decreased back to 0;</li>
  <li>cell's life levels are displayed, not just binary states.</li>
</ul>
State of the field at each iteration is being saved to a file.
