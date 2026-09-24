#ifndef SIGNAL_TREE_H
#define SIGNAL_TREE_H

#include <cstring>
#include <string>
#include <QTextCodec>
#include <QString>
#include <QByteArray>

#include "treenode.h"
#include "mjutils.h"
#include "mj_model_trig_spec.h"

TreeNode * create_model_trig_in_tree(mj_model_trig_t * mj);
TreeNode * create_model_trig_out_tree(mj_model_trig_t * mj);
TreeNode * create_model_trig_params_tree(mj_model_trig_t * mj);

#endif /* SIGNAL_TREE_H */