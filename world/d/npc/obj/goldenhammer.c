// gogogo
#include <ansi.h>
#include <weapon.h>

inherit HAMMER;

void create()
{
        set_name(HIY"��"NOR, ({"golden hammer","hammer" }) );
        set_weight(40000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", 
"����һ���ô������Ĵ����ص���������������˵���������ܺͽ𹿰�����������֪����˭�õı�����\n");
                set("value", 1000000);
                set("no_sell", 1);
                set("no_drop", 1);
                set("material", "gold");
                set("wield_msg", "$N�ó�$n��һ����������ˣ��Ͻ���������������������ѽ��\n");
                set("unwield_msg", "$N�������е�$n,��������һ����������û�ҵ��Լ����ϡ�\n");
        }
        init_hammer(200);
        setup();
}

