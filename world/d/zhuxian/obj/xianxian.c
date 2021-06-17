#include <ansi.h>
#include <weapon.h>
inherit WHIP;
inherit F_UNIQUE;
void create()
{
        set_name( HIG "陷仙鞭" NOR, ({ "xianxian whip", "bian", "whip" }) );
        set_weight(7000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long",
                        
"陷仙鞭\n"
);
                set("value", 0);
                set("material", "steel");
                set("wield_msg", "$N一扬手将$n从手腕上解了下来。\n");
                set("unequip_msg", "$N将$n缠绕在手腕上。\n");
        }
set("no_sell", 1);
 set("no_drop", 1);
 set("no_put",1);
        init_whip(150);
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
        	return HIG "陷仙鞭上绿光闪耀。\n" NOR;
        }
}
 
