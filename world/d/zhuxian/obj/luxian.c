#include <ansi.h>
#include <weapon.h>
inherit STICK;
inherit F_UNIQUE;
void create()
{
        set_name( HIC "¾�ɹ�" NOR, ({ "luxian stick", "stick", "gun" }) );
        set_weight(7000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long",
                        
"¾�ɹ�\n"
);
                set("value", 0);
                set("material", "steel");
                set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
                set("unequip_msg", "$N�����е�$n���ڱ��ϡ�\n");
        }

   set("no_sell", 1);
   set("no_drop", 1);
   set("no_put",1);
        init_stick(150);
        set("is_monitored",1);
        setup();

}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int pro;
        int dam;
        int damage;
        pro = (int) victim->query_temp("apply/armor_vs_spells");
        dam = (int) me->query("force");

        damage = (int) me->query("force_factor");
        if(dam > pro)
        {
		victim->receive_damage("sen",damage/2);
	        victim->receive_damage("kee",damage/2);
		victim->start_busy(1);
        	return HIY "¾�ɹ���Ȼ����ҫ�۵Ĺ�â��$n�۾����������ˡ�\n" NOR;
        }
}
 
