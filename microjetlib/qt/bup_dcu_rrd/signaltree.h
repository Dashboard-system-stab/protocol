#ifndef SIGNAL_TREE_H
#define SIGNAL_TREE_H

#include <cstring>
#include <string>
#include <QTextCodec>
#include <QString>
#include <QByteArray>

#include "treenode.h"
#include "mjutils.h"
#include "mj_bup_dcu_rrd_spec.h"

TreeNode * create_bup_dcu_rrd_in_tree(mj_bup_dcu_rrd_t * mj);
TreeNode * create_bup_dcu_rrd_out_tree(mj_bup_dcu_rrd_t * mj);
TreeNode * create_bup_dcu_rrd_params_tree(mj_bup_dcu_rrd_t * mj);

#endif /* SIGNAL_TREE_H */