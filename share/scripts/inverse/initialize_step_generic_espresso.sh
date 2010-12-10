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
This initializes an espresso simulation

Usage: ${0##*/}

USES: check_deps cp_from_last_step successful_or_die mv

NEEDS:

OPTIONAL: cg.inverse.espresso.blockfile
EOF
   exit 0
fi

check_deps "$0"

esp="$(csg_get_property cg.inverse.espresso.blockfile "conf.esp.gz")"
[ -f "$esp" ] || die "${0##*/}: espresso blockfile '$esp' not found"

cp_from_last_step confout.esp.gz
successful_or_die mv confout.esp.gz $esp

#convert potential in format for sim_prog
for_all non-bonded do_external convert_potential espresso
