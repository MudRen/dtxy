#include <weapon.h>
//  inherit F_UNIQUE;

inherit MACE;
#include <ansi.h>
void create()
{
        set_name("�����", ({"dashen mace", "mace"}));
        set_weight(5000);
if( clonep() )
                set_default_object(__FILE__);
        else {
set("long","һ���Һ�ɫ�ĸֱޣ�ͨ�巺��һ��Ī������Ĺ�â��\n");
                set("unit", "��");
                set("value", 15000);
                set("wield_msg", "$N����һ�죬һ�Ѵ�����ѵ�������\n");
                set("unwield_msg", "$N������$n�������У�\n");
                set("weapon_prop/courage", 20);
                }
        init_mace(100);
        setup();
}
