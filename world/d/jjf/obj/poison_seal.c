// fixed overflow issue by emotion 04/28/2006

#include <skill.h>
#include <ansi.h>

//inherit ITEM;
inherit COMBINED_ITEM;
void create()
{
        set_name("������", ({"poison seal", "seal", "paper"}));
	set_weight(100);
	if(clonep())
    		set_default_object(__FILE__);
  	else {

        set("long","һ�Ż����˷�����ҷ�ֽ�������и����ġ������֡����Լ�(ji)\n");
       set("base_unit","��");
        set("unit", "��");
        set("value", 0);
	set("no_put",1);
	set("no_sell",1);
	}
	set_amount(1);
	setup();
}

void init()
{

  object me = this_object();
  object where = environment();

  if (userp(where))
  {
    if (me->query("owned"))
    {
      if (me->query("owned")!=where->query("id"))
      {
        call_out("destruct_me",1,where,me);
      }
    }
    else
    {
      me->set("owned",where->query("id"));
    }
  }
}

void destruct_me(object where, object me)
{
        object seal;
        if( seal=new("/obj/paper_seal"))
                seal->move(where);
	message_vision("$N���е�$nͻ����⣬���佥����ȥ�����ˡ�\n",where,me);
        destruct(me);
}

void invocation(object who)
{
	float i,a,b,c;

	a=0.0 + who->query("daoxing");
	b=0.0 + (int)who->query_skill("spells");
	b=b*b*b;
	c=0.0 + (int)who->query("mana_factor");
	c=c*c*c;
	i=0.0 + a+b+c;

	this_object()->set("ap",i);
	return;
}
int ji_ob(object victim)
{
	object seal=this_object();
	object me=this_player();
	object where=environment(me);

	int damage, i;
	float ap,dp;

	if( me->query("family/family_name") != "������" )
		return notify_fail("�㲻������ο�����������\n");
	if(me->is_busy())
		return notify_fail("����æ���أ��޷�����������\n");
	if( !victim)
		return notify_fail("��������˲������\n");
	if( where->query("no_magic"))
		return notify_fail("���ﲻ�ܼ���������\n");
	if( !me->is_fighting())
		return notify_fail("ֻ��ս���в��ܼ���������\n");
	if( (int)me->query("mana") < 100 )
		return notify_fail("��ķ������ܿ�����������\n");
	if( (int)me->query("sen") < 100 )
                return notify_fail("��ľ����㣬���Ѽ�Ԧ��������\n");


	message_vision(HIC"\n$N��һ�����š�����һ�ӣ�������һ��$n������\n"NOR, me, seal);
message_vision(HIC"$n��������һ�·ɵ���գ��������Ϊһ����꣬����кɰ���$NϮȥ��\n"NOR,
victim,seal);



	ap= (float)seal->query("ap");
	dp= 0.0 + (int)victim->query_skill("dodge");
	dp=dp*dp*dp*(int)victim->query_kar()/20;;
	dp = dp + (int)victim->query("daoxing")+(int)victim->query("combat_exp");

	if((ap+dp)*random(1000)/1000 > dp/2)	{

                damage = (int)me->query("max_mana") / 20 +
random((int)me->query("eff_kee") / 15);
                damage -= (int)victim->query("max_mana") / 20 +
random((int)victim->query("eff_kee") / 15);
                damage+=(int)me->query("mana_factor")-random((int)victim->query("mana_factor"));

		if( damage> 0){
	message_vision(HIC"\n$N����������������һ������\n"NOR,victim);
		i=damage/20;
		if( i > 20){i=20;}
		if( i < 5 ){i=5;}
		victim->apply_condition("jjf_poison",
(int)victim->query_condition("jjf_poison")+i);
		} else {
			message_vision(HIC"\n$N���˼��������˹�ȥ��\n"NOR,victim);
		}
	}else{
		message_vision(HIC"\n˭֪��$N���˹�ȥ��\n"NOR,victim);
	}

	        if( !victim->is_fighting(me) ) {
                if( living(victim) ) {
                        if( userp(victim) ) victim->fight_ob(me);
                        else
				victim->kill_ob(me);
                }
                me->kill_ob(victim);
        }
	me->add("mana",-50);
        add_amount(-1);
        me->start_busy(1+random(2));
	return 1;
}

int ji (string target)
{
  object seal = this_object ();
  object me = this_player();
  string name=seal->query("name");
  object victim;

  if (!target)
    return notify_fail("�����˭��"+name+"��\n");

  victim=present(target,environment(me));
  seal->ji_ob(victim);
  return 1;
}

