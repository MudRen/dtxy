//made by gogogo
#include <ansi.h>
#include <weapon.h>

inherit SWORD;

void create()
{
        set_name(HIY"������"NOR, ({"dragon xiao","xiao","sword"}));
   set_weight(1000);
   if (clonep())
          set_default_object(__FILE__);
   else {
          set("unit", "��");
          set("long", "һ���������ĵ��ӣ��ഫ����������\n");
          set("value", 100000);
          set("no_sell", 1);
          set("no_drop", 1);
          set("material", "wood");
          set("wield_msg", "$N����$n����ʱ���������ӵ��ӷɳ���\n");
          set("unwield_msg", "$N��$n��������������ɲ�Ǽ���ʧ�ˡ�\n");
          set("music/type", "xiao");
          set("weapon_prop/intelligence", 10);
   }
   init_sword(180);
   set("is_monitored",1);
	setup();
}
int query_autoload() { return 1; }