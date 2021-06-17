#include <weapon.h>

inherit F_UNIQUE;
#include <ansi.h>
inherit SWORD;

void create()
{
        set_name(BLK"Ӱ��"NOR, ({"sword"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "Ӱ���ߵ����������ڰ�ɱ��\n");
                set("no_sell", 1);
                set("no_drop", 1);
                set("no_put", 1);
                set("no_get", 1);
                set("no_break", 1);
                set("value", 30000);
                set("material", "crimsonsteel");
                set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
                set("unequip_msg", "$N�����е�$n��������Ľ��ʡ�\n");
        	set("weapon_prop/intelligence", 10);

        }
        init_sword(210);
        set("is_monitored",1);
        setup();
}
int query_autoload() { return 1; }
/*
void init()
{
        add_action("do_wield","wield");
        add_action("do_unwield", "unwield");
}
object offensive_target(object me)
{
        int sz;
        object *enemy;

        enemy = me->query_enemy();
        if( !enemy || !arrayp(enemy) ) return 0;

        sz = sizeof(enemy);
        if( sz > 4 ) sz = 4;

        if( sz > 0 ) return enemy[random(sz)];
        else return 0;
}

int do_wield (string arg)
{
  object me = this_player();
  object sword = this_object();
  string name = sword->query("name");
  string msg;

if(arg!="all"&&arg != "sword" )
    return notify_fail("��Ҫװ��ʲô��\n");
remove_call_out("conditions");
call_out("conditions",1,me,sword);
  return 0;
}
int do_unwield (string arg)
{
  object me = this_player();
  object sword = this_object();
  string name = sword->query("name");
  string msg;

if ( arg!= "all" && arg != "sword")
    return notify_fail("��Ҫж��ʲô��\n");

  
  sword->set("unwield_msg",msg);
remove_call_out("conditions");
  return 0;
}
void conditions(object who,object ob)
{
     	object target;
     	int ap,dp,damage;
     	string msg;

  	if( who->is_fighting())
	{
        	target = offensive_target(who);
  		if( ! target ) return ;      
 		if( ! present( target,environment(who)) ) return ;    
        	msg = WHT"Ӱ��ͻȻ��ʧ������\n"NOR;

                ap = who->query("combat_exp");
                dp = target->query("combat_exp");

                if( random(ap + dp) > dp/2 )
                 {
                        damage = 600+random(500);
                        damage -= (int)target->query("max_mana") / 10 + random((int)target->query("eff_sen") / 10);
                        damage -= random((int)target->query("mana_factor"));

                        if( damage > 0 ) 
                        {
                                msg += HIC "���$n��ܲ��������������Ķ�����������Ϊ���ء�\n" NOR;
                                target->receive_damage("sen", damage*2);
                                target->receive_wound("sen", damage);
                                target->receive_damage("kee", damage*2);
                                target->receive_wound("kee", damage);
                        } 
            else
                msg += HIC "\n˭֪$nӲ��һ�����������ˡ�\n" NOR;   
                }
                else
                        msg += "���Ǳ�$n�㿪�ˡ�\n";
                message_vision(msg, who, target); 
        }
call_out("conditions",7,who,ob);
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
        victim->receive_damage("sen",damage);
        victim->receive_damage("kee",damage);
        victim->start_busy(1);
        return HIW "���ɽ��ϰ׹�һ����\n" NOR;
        }
}*/

