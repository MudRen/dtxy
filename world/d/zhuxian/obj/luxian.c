#include <ansi.h>
#include <weapon.h>
inherit STICK;
inherit F_UNIQUE;
void create()
{
        set_name( HIC "戮仙棍" NOR, ({ "luxian stick", "stick", "gun" }) );
        set_weight(7000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long",
                        
"戮仙棍\n"
);
                set("value", 0);
                set("material", "steel");
                set("wield_msg", "$N「唰」地一声抽出一根$n握在手中。\n");
                set("unequip_msg", "$N将手中的$n背在背上。\n");
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
        	return HIY "戮仙棍忽然发出耀眼的光芒，$n眼睛都睁不开了。\n" NOR;
        }
}
 
