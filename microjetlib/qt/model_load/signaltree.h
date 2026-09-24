#ifndef SIGNAL_TREE_H
#define SIGNAL_TREE_H

#include <cstring>
#include <string>
#include <QTextCodec>
#include <QString>
#include <QByteArray>

#include "treenode.h"
#include "mjutils.h"
#include "mj_model_load_spec.h"

TreeNode * create_model_load_in_tree(mj_model_load_t * mj);
TreeNode * create_model_load_out_tree(mj_model_load_t * mj);
TreeNode * create_model_load_params_tree(mj_model_load_t * mj);

#endif /* SIGNAL_TREE_H */