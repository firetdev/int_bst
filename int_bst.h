#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
} Node;

void bst_add_node(int value, Node** head_ref) {
	Node* new_node = malloc(sizeof(*new_node));
	if (new_node == NULL) {
		return;
	}

	new_node->data = value;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->parent = NULL;

	Node** current = head_ref;
	Node* parent_node = NULL;
	for (int i = 0; *current != NULL; i++) {
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
}

void bst_free(Node* curr) {
	if (curr == NULL) return;

	Node* left = curr->left;
	Node* right = curr->right;

	free(curr);

	bst_free(left);
	bst_free(right);
}
