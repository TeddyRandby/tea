# TEA

## GUI

### Document
#### Parent Component Node
    * Subclass of component
    * Initialize ncurses
        * Calculate columns and rows

### Component Node
#### Logic
    * Title: array of Word
    * Content: String to display.
    * Parent: Component Node parent
    * Children: Vector of children windows
    * Position: XY position of top left corner. Private.

#### Drawing
    * Render: void function used to change content and titles when logic updates.
        * To draw:
            1. Calculate w and h from parent.
            3. Depending on direction:
                * Fill characters in content until inner width is reached, then loop to new line.
            4. Draw children according to direction.
                * Vertical
                    1. offset child in y direction by sum of previous childrens height.
                * Horizontal
                    1. offset child in x direction by sum of previous childrens width.

    * Width: float 0 ... 1, optional. If not specified and direction is vertical, assume full width.
    * Height: float 0 ... 1, optional If not specified and direction is horizontal, assume full height.

#### Styles    
    * Border: enum of type of border to draw
    * Direction: direction to draw children (vertical, horizontal)
    * Reversed: Should the children be drawn in reverse order?

### Text
#### Word
    * string content
    * Bitmask for ncurses attribute.
    * Can serve as content or title.

#### Line
    * string content
    * Bitmask for ncurses attribute.
    * Can only serve as content.

How to calculate size of component recursively
    1. Either the width or height is fixed and known.
        -If application, fixed by terminal size.
        -If component, fixed by:
         -Proportion of parent
         -Render direction
