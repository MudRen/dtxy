//Cracked by Roath
// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */

inherit ITEM;
#include "task.h"
void create()
{
    set_name("������", ({ "jiaya gu" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "��");
            set("material", "gold");
            set("long", "һ�����Ƶļ�����\n");
            set("owner_name", "���Ϻ��");
          set("owner_id", "xia po");
          }

    setup();
}
