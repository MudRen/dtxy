//modified by vikee for xlqy-zq station
//2000-12-5 9:20
//perform fenguang.
//��ȥ�Է������ͷ�����

// fixed overflow issue, by emotion 04/28/2006

#include <ansi.h>
inherit SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg,str;
        float mypot,tapot;
        int damage,damage_pot;
        weapon = me->query_temp("weapon");
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��ȥ˭��������\n");
                if(me->query("family/family_name") != "��ɽ��" )
                return notify_fail("�����Ķ�͵ѧ�����书��\n");

              if(!me->is_fighting(target))
                return notify_fail("����û���ڴ�ܣ�\n");
        if( time()-(int)me->query_temp("fenguang_end") < 3 )
          return notify_fail("�����ö�Ͳ����ˣ�\n");
        if((int)me->query("max_force") < 400 )
                return notify_fail("����ڹ�̫�\n");

        if((int)me->query("force") < 1000 )
                return notify_fail("����������㣬���ܻ����˵�Ԫ��\n");
         if((int)me->query("mana") < 1000 )
                return notify_fail("��ķ������㣬���ܻ����˵�Ԫ��\n");       
        if((int)me->query("sen") < 100 )
                return notify_fail("��ľ����㣬û����ʩ���⹦��\n");

        if((int)me->query("kee") < 100 )
                return notify_fail("�����Ѫ���㣬û����ʩ���⹦��\n");

 	if((int)me->query_skill("taoism", 1) < 100)
          	return notify_fail("�����ʦ�����ȼ�������ʩ���п��������ѣ�\n");
        if (target->query("force")<100 ||target->query("mana")<100)
                return notify_fail("�Է��������޸���֮�����Ͽ�����ɣ�\n");

        if((int)me->query_skill("hunyuan-zhang",1) < 100)
                return notify_fail("����Ʒ���򻹲�����ʹ����һ�л������ѣ�\n");

	mypot=0.0 + me->query_skill("unarmed");
	mypot=mypot*mypot*mypot/10 + random( (int)me->query("combat_exp"));

        tapot=(0.0 + target->query_skill("dodge")+target->query_skill("parry"))/2;
        tapot=tapot*tapot*tapot/10 + random( (int)target->query("combat_exp"));

        damage_pot=(int)me->query_skill("hunyuan-zhang");

        me->delete("env/brief_message");
	target->delete("env/brief_message");
	message_vision(HIW"\n$N�����񣬿��������\n",me,target);
	message_vision(HIR"\n�����񣬽���ף�����⣬ͬ�䳾��\n",me,target);
	message_vision(HIW"\n$Nһ����ͻȻ��òҰף�����ֱ�����͵ض�׼$n�����д�Ѩ������ȥ��\n"NOR,me,target);


	if ( ( mypot + tapot ) * random(1000) / 1000 > tapot/3 )
	{
     	message_vision(HIR"\n$n����һ�����ȣ����ļ�����Ż��������Ѫ����ɫ�԰�����࣡\n"NOR,me,target);

          damage=damage_pot*2+random(damage_pot);
          //���һ��mindsword=200��player�����������Χ��400-1000.

	    target->add("force",-damage);
            if ((int)target->query("force")<0)
             {
             	target->set("force",0);
		message_vision(HIR"$n�����������������޸���֮����\n"NOR);
		str=target->name()+HIM"��"NOR+HIC"����"+HIM"��"+me->name()+"����ɽ��ѧ"NOR+HIW"���׹⻯Ӱ��"+HIM"���������޸���֮����";
		if( !random(5) ) message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
	     }

	     target->add("mana",-damage);

	     if ((int)target->query("mana")<0)
	     {
	     	target->set("mana",0);
	     	message_vision(HIR"$n�ķ��������������޸���֮����\n"NOR);
	     	str=target->name()+HIM"��"NOR+HIC"����"+HIM"��"+me->name()+"����ɽ��ѧ"NOR+HIW"���׹⻯Ӱ��"+HIM"���������޸���֮����";
		if( !random(5) ) message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
	     }
           	//ʩ��������һ���������ͷ�����100 pot �ľ�����Ϊ���ۡ�
           	me->add("force", -damage/8);
           	me->add("mana",-damage/8);
           	me->receive_damage("sen", 100);

           	if ((int)me->query("force")<0) me->set("force",0);

        }

        else
     	message_vision(HIY"\n$n����һ�Σ������$N�Ĺ�����\n"NOR,me,target);
        me->set_temp("fenguang_end",time());
        return 1;
}


