#! /bin/bash
# 
# Copyright 2009 The VOTCA Development Team (http://www.votca.org)
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

if [ "$1" = "--help" ]; then
cat <<EOF
${0##*/}, version %version%
This script implemtents the function update
for the Simplex Method

Usage: ${0##*/}

USES:  die msg csg_get_property for_all do_external

NEEDS: cg.inverse.program
EOF
   exit 0
fi

check_deps "$0"

msg "Calc rdf"
sim_prog="$(csg_get_property cg.inverse.program)"
for_all non-bonded do_external rdf $sim_prog

main_dir=$(get_main_dir);
name=$(csg_get_interaction_property name);
step_nr=$(get_current_step_nr);
init_steps=$(wc -l $main_dir/simplex.in | awk '{print ($1)}');
p_nr=$(grep -c '^p' simplex.cur);
a_nr=$(grep -c '^a' simplex.cur);
p_line_nr=$(grep -n -m1 '^p' simplex.cur | sed 's/:.*//');
a_line_nr=$(grep -n -m1 '^a' simplex.cur | sed 's/:.*//');

if [ $p_nr -gt "1" ]; then
   msg "Calc ftar"
   run_or_exit do_external update simplex_ftar ${name}.dist.tgt ${name}.dist.new \
   simplex.cur simplex.new $(($p_line_nr-1))
   run_or_exit do_external update simplex_step simplex.cur simplex.new $p_line_nr
elif [ $step_nr -eq $init_steps ]; then
   msg "Calc ftar"
   run_or_exit do_external update simplex_ftar ${name}.dist.tgt ${name}.dist.new \
   simplex.cur simplex.tmp $(($p_line_nr-1))
   msg "Preparing new parameters"
   run_or_exit do_external update simplex_step simplex.tmp simplex.new $init_steps
else
   msg "Calc ftar"
   run_or_exit do_external update simplex_ftar ${name}.dist.tgt ${name}.dist.new \
   simplex.cur simplex.tmp $init_steps
   msg "Preparing new parameters"
   run_or_exit do_external update simplex_step simplex.tmp simplex.new $init_steps
fi

for_all non-bonded do_external update simplex_single