//jueshi.c by yushu 2000.11
#include <weapon.h>
#include <ansi.h> 
inherit F_UNIQUE;
inherit SWORD;
void create()
{
        set_name(HIC"С��"NOR, ({"jiansheng xinwu","xinwu","sword","jian"}));
        set_weight(50000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
              set("unit", "��");
              set("long", "һ�ѿ��ƺ���ͨ��С��,Ҳ��֪����ʲô�ã�\n");
              set("no_sell", 1); 
         //     set("no_give", 1);
              set("no_drop", 1);
              set("no_put", 1);
              set("value", 1); 
              set("replace_file", "/d/obj/weapon/sword/qinghong");
              set("material", "gold");
              set("wield_msg", "$N��ৡ���һ�����һ��$n�������У�\n");
              set("unwield_msg", "$N�����е�$n�������䣮\n");
              set("weapon_prop/int", 2);

        }
        init_sword(50); 
   //     set("is_monitored",1);
        setup();
}