//Cracked by Roath
// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
inherit ITEM;
#include "task.h"
void create()
{
    set_name("ѹ����", ({ "hongbao" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "��");
            set("material", "cloth");
            set("long", "һ��СС�ĺ������С����ѹ��Ǯ��\n");
            set("owner_name", "�Ϻ���");
          set("owner_id", "xifuhui boss");
          }
    setup();
}
