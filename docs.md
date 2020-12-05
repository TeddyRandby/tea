# TEA

## GUI

Keep windows in a tree?

### Window Node
    * Render: Function called to generate content. 
    * Content: array of lines
    * Children: Vector of pointers to children windows
    * Border: enum of type of border to draw
    * size: WH tuple, ((hasborder * 2) + widest line, (hasborder*2) + num lines) + size(children)
        * If drawing lr or lrr, sum children width and take highest children height.
        * If drawing ud or udr, sum children height and take highest children width.
    * Direction: direction to draw children (vertical, horizontal)
    * Reversed: Should the children be drawn in reverse order?
