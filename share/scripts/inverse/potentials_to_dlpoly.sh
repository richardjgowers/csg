#! /bin/bash
#
# Copyright 2009-2013 The VOTCA Development Team (http://www.votca.org)
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

if [[ $1 = "--help" ]]; then
cat <<EOF
${0##*/}, version %version%
This script converts all potentials to the format needed by dlpoly

Usage: ${0##*/}
EOF
   exit 0
fi

[[ -f TABLE ]] && echo "We will now overwrite TABLE"
echo "Table for dlpoly from VOTCA with love" > TABLE #max 100 chars
bin_size="$(csg_get_property cg.inverse.dlpoly.table_bins)"
table_end="$(csg_get_property cg.inverse.dlpoly.table_end)"
# see dlpoly manual ngrid = int(cut/delta) + 4
ngrid="$(csg_calc $table_end / $bin_size)"
ngrid="$(to_int $ngrid)"
ngrid="$(($ngrid+4))"
echo "$bin_size $table_end $ngrid" >> TABLE
for_all "non-bonded" do_external convert_potential dlpoly '$(csg_get_interaction_property name).pot.cur' '$(csg_get_interaction_property name).pot dlpoly'