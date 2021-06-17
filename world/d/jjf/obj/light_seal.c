#include <skill.h>
#include <ansi.h>

//inherit ITEM;
inherit COMBINED_ITEM;
void create()
{
        set_name("�����編��", ({"light seal", "seal", "paper"}));
	set_weight(100);
	if(clonep())
    		set_default_object(__FILE__);
  	else {

        set("long","һ�Ż����˷�����ҷ�ֽ�������и����ġ��硱�֡����Լ�(ji)\n");
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

	a=0.0 + who->query("combat_exp");
	b=0.0 + (int)who->query_skill("spells");
	b=b*b;
	c=0.0 + (int)who->query("mana_factor");
	c=c*c*c;
	i=0.0+a+b+c;

	this_object()->set("ap",i);
	return;
}
int ji_ob(object victim)
{
	object seal=this_object();
	object me=this_player();
	object where=environment(me);

	int success_adj, damage_adj;
	success_adj = 175;
	damage_adj = 145;

	if(me->is_busy())
		return notify_fail("����æ���أ��޷��������編����\n");
	if( me->query("family/family_name") != "������" )
		return notify_fail("�㲻������ο��������編����\n");
	if( !victim)
		return notify_fail("��������˲������\n");
	if( where->query("no_magic"))
		return notify_fail("���ﲻ�ܼ������編����\n");
	if( !me->is_fighting())
		return notify_fail("ֻ��ս���в��ܼ������編����\n");
	if( (int)me->query("mana") < 100 )
		return notify_fail("��ķ������ܿ��������編����\n");
	if( (int)me->query("sen") < 100 )
                return notify_fail("��ľ����㣬���Ѽ�Ԧ�����編����\n");

        me->add("mana", -50);
	SPELL_D->attacking_cast(
		me,
			//attacker
		victim,
			//target
		success_adj,
			//success adjustment
		damage_adj,
			//damage adjustment
		"qi",
			//damage type: could be "qi"/"kee", "shen"/"sen", ...default "both"
		HIC "\n$N��һ�����š�����һ�ӣ�������һ�������編����\n�����編����������һ�·ɵ���գ�ֻ����������������һ����������$n��\n" NOR,
			//initial message
		HIR "\n$n����������������͸��������ϳ�һ��������Ѫ����\n" NOR,
			//success message
		HIC "\n$n���˼��������˹�ȥ��\n" NOR,
			//fail message
		HIC "����$n��ָһ��������һ���������編������$N��ȥ��\n" NOR,
			//backfire initial message
		HIR "����ˣ���һ�������編����$n��������������\n" NOR
			//backfire hit message. note here $N and $n!!!
	);

        me->start_busy(1+random(1));
	add_amount(-1);
	// destruct(seal);
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

