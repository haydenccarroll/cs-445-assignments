#include <cstdio>
#include <cstring>

// // // // // // // // // // // // // // // // // // // // // //
//
//  EXAMPLES OF SIMPLE TREE TRAVERSALS
//
//  This file contains a simple TreeNode class that holds a char *
//  name. The treenodes can be assembled into a tree using TreeNode
//  pointers. An example tree is constructed by hand using pointers in
//  a very delierate way. The tree is then printed in a number of ways
//  by traversing it with various recursive demonstration functions.
//

// the maximum number of children each node can have
#define MAXCHILDREN 2

// // // // // // // // // // // // // // // // // // // // // //
//
// class TreeNode: a simple pointer based tree class
//
class TreeNode {
public:
    TreeNode *child[MAXCHILDREN];
    char *name;

public:
    TreeNode(char *n) {
        name = strdup(n);
        for (int i=0; i<MAXCHILDREN; i++) child[i] = NULL;
    }

    // print name of node indented by depth
    void print(int depth) {
        for (int i=0; i<depth; i++) printf("   ");
        printf("%s", name);
    }
};



// // // // // // // // // // // // // // // // // // // // // //
//
// Several different traversals using prefix, infix, postfix, and a
// combination
//

// PREFIX TRAVERSAL This does work in the node before it dives down to
//  each child. In our super simple example it just displays the name
//  associated with the node. but it could do much more complex things
//  with respect to the node before visiting the children.
//
//  This is what the Louden used to print a tree in the Tiny compiler.
//
void traversePrefix(TreeNode *t, int depth)
{
    if (t==NULL) return;
    t->print(depth); printf("\n");
    traversePrefix(t->child[0], depth+1);
    traversePrefix(t->child[1], depth+1);
}


// INFIX TRAVERSAL This does work in the node strictly between the
//  recursions on children. So it traverses child0 then does work in
//  the node itself and then it traverses child1
//
void traverseInfix(TreeNode *t, int depth)
{
    if (t==NULL) return;
    traverseInfix(t->child[0], depth+1);
    t->print(depth); printf("\n");
    traverseInfix(t->child[1], depth+1);
}


// POSTFIX TRAVERSAL This visits the children first and then does work
//  in the node.
//
void traversePostfix(TreeNode *t, int depth)
{
    if (t==NULL) return;
    traversePostfix(t->child[0], depth+1);
    traversePostfix(t->child[1], depth+1);
    t->print(depth); printf("\n");
}


// traversal showing an action done before, after and between EACH
//  child! This is a combination of what we have seen above. It can do
//  some work in the node initially and then traverse child0 and then
//  do more work and then child1 and then more work and then child2...
//  and finally do some work and leave. If the number of children is
//  greater than 2 then you can just call more traverses and put
//  actions between them as well. For example: 6 children means 7
//  possible places to do something. In this example, output is a
//  single line (depth is ignored)
//
//  This is more what Louden does in the code generation traverasal
//  (cgen) in the Tiny compiler.
//
void traverseFormula(TreeNode *t, int depth)
{
    if (t==NULL) return;
    printf("(");                            // before
    traverseFormula(t->child[0], depth+1);
    printf("%s", t->name);                  // between
    traverseFormula(t->child[1], depth+1);
    printf(")");                            // after
}


//  In this traversal each node is shown as if it is a function
//  applied to all it's children. The function name is the node name.
//  If there are no children just the name is printed. Output is a
//  single line.
//
void traverseFunction(TreeNode *t, int depth)
{
    int numChildren;

    if (t==NULL) return;
    numChildren = (t->child[0] ? 1 : 0) + (t->child[1] ? 1 : 0);
    printf("%s", t->name);
    if (numChildren>0) printf("(");
    traverseFunction(t->child[0], depth+1);   // visit child0
    if (numChildren==2) printf(", ");
    traverseFunction(t->child[1], depth+1);   // visit child1
    if (numChildren>0) printf(")");
}


// // // // // // // // // // // // // // // // // // // // // //
//
// Test the tree and types of traversals.
//
// Uses a hand built taxonomic tree of mammals
//
int main()
{
    TreeNode *root, *l, *r, *ll, *lr, *lll, *llr, *lrr, *rl, *rr;

    // the root node name root
    root = new TreeNode((char *)"Mammal");

    // root's children
    l = new TreeNode((char *)"Odd-toes");
    r = new TreeNode((char *)"Even-toes");
    root->child[0] = l;
    root->child[1] = r;

    // odd toes
    ll = new TreeNode((char *)"Equus");
    lr = new TreeNode((char *)"Rhino");
    l->child[0] = ll;
    l->child[1] = lr;

    // Rhinos
    lrr = new TreeNode((char *)"Javan");
    lr->child[1] = lrr;

    // equus
    lll = new TreeNode((char *)"Horse");
    llr = new TreeNode((char *)"Zebra");
    ll->child[0] = lll;
    ll->child[1] = llr;

    // even toes
    rl = new TreeNode((char *)"Giraffe");
    rr = new TreeNode((char *)"Camel");
    r->child[0] = rl;
    r->child[1] = rr;


    printf("\n---Prefix\n");
    traversePrefix(root, 0);

    printf("\n---Infix\n");
    traverseInfix(root, 0);

    printf("\n---Postfix\n");
    traversePostfix(root, 0);

    printf("\n---Processing nodes as operators using before, between, and after\n");
    traverseFormula(root, 0);
    printf("\n");

    printf("\n---Print out as a function applied to children\n");
    traverseFunction(root, 0);
    printf("\n");

    return 0;
}