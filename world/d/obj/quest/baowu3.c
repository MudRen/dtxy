//Cracked by Roath
// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
inherit ITEM;
#include "task.h"
void create()
{
        set_name("������", ({"huolong biao"}));
        set_weight(80);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "ֻ�������ߴ���֣��ų����⣬�����Ŀ����Ի�����Ķ�����\n");
                set("unit", "��");
                set("lingtaibao","fake");
               set("owner_name","��������");
                     set("owner_id","master yunyang");
        }
}
