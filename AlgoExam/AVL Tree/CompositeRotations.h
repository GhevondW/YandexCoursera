/***
 * https://www.programiz.com/dsa/avl-tree
 * Left-Right and Right-Left Rotate
 * In left-right rotation, the arrangements are first shifted to the left and then to the right.
 * 
 * 1. Do left rotation on x-y.
 * 2. Do right rotation on y-z.
 * 
 *         (1)
 *                      p                                     p
 *                      |                                     |
 *                     (z)                                   (z)
 *                    /   \                                 /   \
 *                  (x)    f             ->               (y)    f
 *                 /   \                                 /   \
 *                a    (y)                             (x)    g
 *                    /   \                           /   \
 *                   b     g                         a     b
 * 
 *         (2)
 * 
 *                      p                                     p                    
 *                      |                                     |                    
 *                     (z)                                   (y)           
 *                    /   \                                 /   \                    
 *                  (y)    f                             (x)     (z)                     
 *                 /   \                 ->              / \     / \                               
 *               (x)    g                               a   b   g   f                     
 *              /   \
 *             a     b
 * 
 * 
 * In right-left rotation, the arrangements are first shifted to the right and then to the left.
 * 
 * 1. Do right rotation on x-y.
 * 2. Do left rotation on z-y.
 * 
 *         (1)
 *                      p                                     p
 *                      |                                     |
 *                     (z)                                   (z)
 *                    /   \                                 /   \
 *                   f    (x)             ->               f    (y)    
 *                       /   \                                 /   \
 *                     (y)    a                               g    (x)    
 *                    /   \                                       /   \
 *                   g     b                                     b     a
 * 
 *         (2)
 * 
 *                      p                                        p                         
 *                      |                                        |      
 *                     (z)                                      (y)
 *                    /   \                                    /   \
 *                   f    (y)            ->                  (z)   (x)
 *                       /   \                              /   \ /   \
 *                      g    (x)                           f    g b    a
 *                          /   \
 *                         b     a
 * 
 * */
