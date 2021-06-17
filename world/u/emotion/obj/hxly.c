#include <weapon.h>
#include <ansi.h>
inherit SWORD;

void create()
{
        set_name(HIW"��Х����"NOR, ({"hxly"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "��˵Ϊ�������������Ƶ�������������, ������Ծ������챦��\n");
                set("no_sell", 1);
                set("no_drop", 1);
                set("no_put", 1);
                set("no_break", 1);
                set("no_get", 1);
                set("value", 30000);
                set("material", "crimsonsteel");
                set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
                set("unequip_msg", "$N�����е�$n��������Ľ��ʡ�\n");
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
    return notify_fail("��Ҫװ��ʲô��\n");
  msg = "$N����һ��"+name+"�������������һ��Х������\n";
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
    return notify_fail("��Ҫ��ʲô��\n");
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
    return notify_fail("��Ҫж��ʲô��\n");

  msg = "$N��"+name+"���˻�ȥ����\n";
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
			tell_object(env, HIR"��·�����������˵����Х����Ӧ�û������ˡ�\n"
		                 + "����һ�����죬��Х�������ڿն�ȥ��������һ˿�ۼ���\n\n"NOR);
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
        msg = HIW"��Х����ͻȻ���ַɳ���\n"NOR;

                ap = 10000000;
                dp = target->query("combat_exp");

                if( random(ap + dp) > dp )
                 {
                        damage = 1200+random(1000);
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
        			msg += "��Х�����ϰ׹�һ��, " + victim->query("name") + "��������������" + me->query("name")
        			       + "����\n";
					break;
				case 1:
					victim->add("force",-damage);
					victim->add("mana",-damage);
					me->add("force",damage);
					me->add("mana",damage);
        			msg += "��Х����������һ��, " + victim->query("name") + "�������ͷ�����������" + me->query("name")
        			       + "����\n";
					break;
				case 2:
					victim->receive_damage("sen",damage);
					victim->receive_damage("kee",damage);
					me->add("combat_exp",victim->query("combat_exp")/100);
					me->add("daoxing",victim->query("daoxing")/100);
        			msg += "��Х�����Ϻ��һ��, " + me->query("name") + "����ѧ�͵�����ʱ������\n";
					break;
			}
        	victim->start_busy(2);
        	return HIW + msg + NOR;
        }
}

