#include <stdlib.h>

typedef struct Node {
	int data;
	int height;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
} Node;

void bst_update_height(Node* v);  // Forward declaration

void bst_add_node(int value, Node** head_ref) {
	Node* new_node = malloc(sizeof(*new_node));
	if (new_node == NULL) return;

	new_node->data = value;
	new_node->height = 0;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->parent = NULL;

	Node** current = head_ref;
	Node* parent_node = NULL;
	while (*current != NULL) {
		parent_node = *current;
		new_node->parent = parent_node;
		if (value < (*current)->data) {
			current = &(*current)->left;
		} else if (value > (*current)->data) {
			current = &(*current)->right;
		} else {
			free(new_node);
			return;
		}
	}

	*current = new_node;
	new_node->parent = parent_node;
	bst_update_height(parent_node);
}

void bst_free(Node* curr) {
	if (curr == NULL) return;

	Node* left = curr->left;
	Node* right = curr->right;

	free(curr);

	bst_free(left);
	bst_free(right);
}

Node* bst_search(Node* v, int target) {
	if (v == NULL || v->data == target) return v;
	if (target < v->data) return bst_search(v->left, target);
	return bst_search(v->right, target);
}

Node* bst_min(Node* v) {
	if (v == NULL || v->left == NULL) return v;
	return bst_min(v->left);
}

Node* bst_max(Node* v) {
	if (v == NULL || v->right == NULL) return v;
	return bst_max(v->right);
}

// Wrapper for calling bst_get_successor with 1 parameter
Node* bst_successor(Node* v) {
	if (v == NULL) return v;
	return bst_get_successor(v, v);
}

// NOTE: this recursive algorithm runs at O(h^2), which, in a perfect tree, is O(log^2 n),
// and can decay in the worst case to O(n^2)
// By contrast, the standard iterative solution is O(h), which is O(log n) in a perfect
// tree and decays to O(n). The recursive solution is always worse. It is included
// simply because I came up with it and this project is just for fun.
Node* bst_get_successor(Node* v, Node* origin) {
	if (v == NULL) return v;

	if (v->right != NULL) {
		if (bst_min(v->right)->data > origin->data) {
			return bst_min(v->right);
		}
	}
	if (v->parent != NULL && v == v->parent->left) return v->parent;
	if (v->parent != NULL) return bst_get_successor(v->parent, origin);
	return NULL;
}

int bst_get_height(Node* v) {
	return (v == NULL) ? -1 : v->height;
}

void bst_update_height(Node* v) {
	if (v == NULL) return;

	int left_h = bst_get_height(v->left);
	int right_h = bst_get_height(v->right);
	v->height = 1 + (left_h > right_h ? left_h : right_h);

	bst_update_height(v->parent);
}

int bst_get_depth(Node* v) {
	return (v == NULL) ? -1 : 1 + bst_get_depth(v->parent);
}
