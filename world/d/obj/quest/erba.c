//Cracked by Roath
// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
inherit ITEM;

#include <task.h>
void create()
{
        set_name("�������", ({"er ba", "ba zi"}));
        set_weight(80);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "˳����Ķ������.\n");
                set("unit", "��");
               set("owner_name","˳���");
              set("owner_id","shunfeng er");
        }
}
