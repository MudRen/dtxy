#include <weapon.h>
#include <ansi.h>
inherit SWORD;

void create()
{
        set_name(HIW"虎啸龙吟"NOR, ({"hxly"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "传说为天神易吾心炼制的威镇三界五行, 神佛妖皆惧的奇兵异宝。\n");
                set("no_sell", 1);
                set("no_drop", 1);
                set("no_put", 1);
                set("no_break", 1);
                set("no_get", 1);
                set("value", 30000);
                set("material", "crimsonsteel");
                set("wield_msg", "$N「唰」地一声抽出一把$n握在手中。\n");
                set("unequip_msg", "$N将手中的$n插入腰间的剑鞘。\n");
        }
        init_sword(600);
        set("countdown", 5);
        set("is_monitored",1);
        setup();
        call_out("check_owner", 60);
}
void init()
{
    add_action("do_wield","wield");
    add_action("do_unwield", "unwield");
    add_action("do_unlock", "unlock");
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

if(arg!="all"&&arg != "hxly" )
    return notify_fail("你要装备什么？\n");
  msg = "$N拿起一把"+name+"，你耳旁响起了一阵虎啸龙吟。\n";
  sword->set("wield_msg",msg);
remove_call_out("conditions");
call_out("conditions",1,me,sword);
  return 0;
}

int do_unlock (string arg)
{
  object sword = this_object();
  string name = sword->query("name");
  string msg;

if(arg!="hxly ywxdtxy" )
    return notify_fail("你要干什么？\n");
set("owner",this_player());
set("countdown", 5);
return 1;
}

int do_unwield (string arg)
{
  object me = this_player();
  object sword = this_object();
  string name = sword->query("name");
  string msg;

if ( arg!= "all" && arg != "hxly")
    return notify_fail("你要卸下什么？\n");

  msg = "$N将"+name+"收了回去……\n";
  sword->set("unwield_msg",msg);
remove_call_out("conditions");
  return 0;
}

void check_owner( ) {
        object env;
        env = environment(this_object());
	if (!env)
		return;
	if ( env!= query("owner") ) {
		delete("owner");
		add("countdown", -1);
		if ( query("countdown") <= 0 ) {
			tell_object(env, HIR"你仿佛听到易吾心说：虎啸龙吟应该还给我了。\n"
		                 + "随着一声轻响，虎啸龙吟已腾空而去，不留下一丝痕迹。\n\n"NOR);
			destruct(this_object());
			return;
		}
        }
	call_out("check_owner", 60);
}

void conditions(object who,object ob)
{
     object target;
     int ap,dp,damage;
     string msg;

string type;
type = ob->query("armor_type");
if( who->query_temp("armor/" + type) && ob->query("equipped")!="worn")
return;
  if( who->is_fighting())
     {
        target = offensive_target(who);
  if( ! target ) return ;
 if( ! present( target,environment(who)) ) return ;
        msg = HIW"虎啸龙吟突然脱手飞出！\n"NOR;

                ap = 10000000;
                dp = target->query("combat_exp");

                if( random(ap + dp) > dp )
                 {
                        damage = 1200+random(1000);
                        damage -= (int)target->query("max_mana") / 10 + random((int)target->query("eff_sen") / 10);
                        damage -= random((int)target->query("mana_factor"));

                        if( damage > 0 )
                        {
                                msg += HIC "结果$n躲避不及，被长剑穿心而过，伤势颇为惨重。\n" NOR;
                                target->receive_damage("sen", damage*2);
                                target->receive_wound("sen", damage);
                                target->receive_damage("kee", damage*2);
                                target->receive_wound("kee", damage);
                        }
            else
                msg += HIC "\n谁知$n硬接一剑，毫发无伤。\n" NOR;
                }
                else
                        msg += "但是被$n躲开了。\n";
                message_vision(msg, who, target);
        }
call_out("conditions",4,who,ob);
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
        int pro;
        int dam;
        int damage;
        string msg = "";
        pro = (int) victim->query_temp("apply/armor_vs_spells");
        dam = (int) me->query("force");

        damage = 2 * (int) me->query("force_factor");
        if(dam > pro)
        {
			switch(random(3)) {
				case 0:
				default:
					victim->receive_damage("sen",damage);
					victim->receive_damage("kee",damage);
					me->receive_curing("sen", damage);
					me->receive_curing("kee", damage);
        			msg += "虎啸龙吟上白光一闪, " + victim->query("name") + "的气和神被吸入了" + me->query("name")
        			       + "体内\n";
					break;
				case 1:
					victim->add("force",-damage);
					victim->add("mana",-damage);
					me->add("force",damage);
					me->add("mana",damage);
        			msg += "虎啸龙吟上篮光一闪, " + victim->query("name") + "的内力和法力被吸入了" + me->query("name")
        			       + "体内\n";
					break;
				case 2:
					victim->receive_damage("sen",damage);
					victim->receive_damage("kee",damage);
					me->add("combat_exp",victim->query("combat_exp")/100);
					me->add("daoxing",victim->query("daoxing")/100);
        			msg += "虎啸龙吟上红光一闪, " + me->query("name") + "的武学和道行立时增加了\n";
					break;
			}
        	victim->start_busy(2);
        	return HIW + msg + NOR;
        }
}

