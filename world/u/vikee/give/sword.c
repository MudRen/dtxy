// blade.c

#include <weapon.h>

inherit SWORD;

void create()
{
        set_name("��罣", ({"qinghong sword", "sword", "jian",
"qinghong"}));
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","һ��������ħ�ı�����\n");
                set("unit", "��");
		set("wield_msg",
"$n��ৡ��شӽ����е���������$N�����У����⻹أ��������ͣ��\n");
		set("unwield_msg",
"$N�����е�$n�������䣬��ɫ���������ˣ�\n");
                set("value", 5000);
		set("weapon_prop/courage", 10);
		set("no_sell",1);
				set("no_drop","ȥ�����Ѷ��ɣ����ӻ���Ⱦ����!\n");
				set("no_give","�ܹܷ���װ�����ɲ���������Ӵ��\n");
				set("no_get","�����ܹ�һҶ֪�﷢��װ�������ΰ�!\n");
        }
        init_sword(70);
        setup();
}
