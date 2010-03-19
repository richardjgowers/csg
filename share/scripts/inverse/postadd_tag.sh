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
This script implemtents smoothing of the potential update (.dpot)

Usage: ${0##*/}

USES: die csg_get_interaction_property log check_deps get_table_comment

NEEDS: name
EOF
   exit 0
fi

check_deps "$0"

name=$(csg_get_interaction_property name)
comment="$(get_table_comment)"
input="${name}.pot.cur"
output="${name}.pot.new"

[ -f "${name}.pot.cur" ] || die "${0##*/}: could not find ${name}.pot.cur"

log "${0##*/}: Taging file $output"
echo -e "$comment" | sed 's/^/#/' > "$output" || die "${0##*/}: sed failed"
cat "$input" >> "$output" || die "${0##*/}: cat failed"

