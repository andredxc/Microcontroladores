/*
    Universidade Federal do Rio Grande do Sul
    Escola de Engenharia
    Departamento de Sistemas Elétricos de Automação e Energia
    Microcontroladores ENG10032

    André Dexheimer Carneiro 00243653
    Camilla Stefani Schmidt 00237738
    Henrique Ecker Pchara 00213945

    This API provides basic controls over the Quanser 2DSFJE Robot

    Copyright (c) 2018 André Dexheimer Carneiro, Camilla Stefani Schmidt and Henrique Ecker Pchara

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

    You can also obtain a copy of the GNU General Public License
    at <http://www.gnu.org/licenses>.

*/
#include "api.h"

int main(){

    int done;

    if(init() < 0){
        fprintf(stderr, "%s - Couldn't initialize api\n", __FUNCTION__);
        return -1;
    }

	fprintf(stderr, "Waiting...\n");

    done = 0;
    while(!done){

        if(readElbow1()){
            fprintf(stderr, "ELB1\n");
        }

        if(readElbow2()){
            fprintf(stderr, "ELB2\n");
        }
    }

    finish();
    return 1;
}
