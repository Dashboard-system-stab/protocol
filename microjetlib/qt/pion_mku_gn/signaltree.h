#ifndef SIGNAL_TREE_H
#define SIGNAL_TREE_H

#include <cstring>
#include <string>
#include <QTextCodec>
#include <QString>
#include <QByteArray>

#include "treenode.h"
#include "mjutils.h"
#include "mj_pion_mku_gn_spec.h"

TreeNode * create_pion_mku_gn_in_tree(mj_pion_mku_gn_t * mj);
TreeNode * create_pion_mku_gn_out_tree(mj_pion_mku_gn_t * mj);
TreeNode * create_pion_mku_gn_params_tree(mj_pion_mku_gn_t * mj);

#endif /* SIGNAL_TREE_H */