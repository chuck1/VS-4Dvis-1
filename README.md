
# N-Space

## Data Transfer

We must defined how data will be transfer between the CPU and GPU representations of objects.

Object on the CPU will

## sequence

 * input
 * physics
 * render
   * ray cast
     * for each origin ray in the viewport
       * find closest intersection with a face. if no intersection, set pixel to black
       * for each light source
         * cast ray from intersection point to light source
         * if intersects shape before light, return black
         * add contribution
       * if surface has reflectivity, cast a new view ray and add its result
