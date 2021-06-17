#include <ansi.h>
#include <weapon.h>
inherit SPEAR;
inherit F_UNIQUE;
void create()
{
        set_name( HIR "诛仙枪" NOR, ({ "zhuxian spear", "spear"}) );
        set_weight(7000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long",
                        
"诛仙枪\n"
);
                set("value", 0);
                set("material", "steel");
                set("wield_msg", "$N「唰」地一声抽出一根$n握在手中。\n");
                set("unequip_msg", "$N将手一反将$n隐在身后。\n");
        }
set("no_sell", 1);
 set("no_drop", 1);
 set("no_put",1);
        init_spear(150);
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
        	return HIR "诛仙枪闪出妖异的红光。\n" NOR;
        }
}
 
