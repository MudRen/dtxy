//edit by yesi
//lestat modi for hell
#include <ansi.h>
inherit SSERVER;

int perform(object me, object target)
{
  object weapon;
  int damage,enhance;   
  string msg,str;
  int cd = 5;   
  if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ��һ�С����ˡ�����\n");
        if(me->query("family/family_name") != "���޵ظ�")
                return notify_fail(HIG"�����ˡ���"+NOR"��ڤ�粻��֮�ܣ�\n");
        if(!me->is_fighting())
                return notify_fail("�����ˡ���ֻ����ս����ʹ�ã�\n");
        if((int)me->query("force") < 1000 )
                return notify_fail("�������������\n");
//        if (me->query_temp("ldlh"))
//           return notify_fail("������ʩ�ò������ֻ�����û�������������ˡ�����\n");
        if((int)me->query("kee") < 300 )
                return notify_fail("�����Ѫ���㣬û����ʩ���⹦��\n");
        
	if( me->query("lunhui_zhuanshi") )
		cd = 4;
        if( time()-(int)me->query_temp("three_end") < cd )
          return notify_fail("�����ö�Ͳ����ˣ�\n");
        if((int)me->query_skill("kusang-bang", 1) < 150)
                return notify_fail("��Ŀ�ɥ�����𻹲�����ʹ����һ�л������ѣ�\n");
        if((int)me->query_skill("hellfire-whip", 1) < 150)
                return notify_fail("����һ�޼��𻹲�����ʹ����һ�л������ѣ�\n");
        if((int)me->query_skill("jinghun-zhang", 1) < 150)
                return notify_fail("��ľ����Ƽ��𻹲�����ʹ����һ�л������ѣ�\n");
        if (me->query_skill_mapped("unarmed")!="jinghun-zhang")
                return notify_fail("�����ˡ���������Ͼ����Ʋ���ʹ�á�\n");
        if (me->query_skill_mapped("stick")!="kusang-bang")
                return notify_fail("�����ˡ���������Ͽ�ɥ������ʹ�á�\n");              

    weapon=me->query_temp("weapon");
//    target->start_busy(1);//��ס���ַ�ֹ��ʧͬʱ���������е�����.
    message_vision(HIW"\n$N˫�ֻ�һ��Բ����Ȼ������٣������������������������ˡ����ˡ������С�\n"NOR,me,target);
//����
    message_vision(HIB"\n�����׹��㣬$N�趯"+weapon->name()+NOR+HIB"������һЦ������$n��\n"NOR,me,target);
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
    seteuid(getuid());
//����
    me->set("actions", (: call_other, SKILL_D("jinghun-zhang"), "query_action" :) );
    weapon->set_temp("original/use_apply_skill",weapon->query("use_apply_skill"));
    weapon->set_temp("original/skill_type",weapon->query("apply/skill_type"));
    weapon->set("use_apply_skill",1);
    weapon->set("apply/skill_type","unarmed");
    enhance=me->query_skill("jinghun-zhang",1);
    me->add_temp("apply/attack", enhance);  
    damage=me->query_skill("tonsillit",1);
    damage=damage/2;
    me->add_temp("apply/damage",damage);    
    message_vision(HIB"\n����������Ӱ����Ʈ����ͻȻ$N��һ������������ץ��$n��\n"NOR, me,target);    
    COMBAT_D->do_attack(me, target);
    me->add_temp("apply/attack",-enhance);
//����
    message_vision(HIB"\n$N˫��һ��������"+weapon->name()+NOR+HIB"��ʱ��ı�ֱ����ͬһ��������\n"NOR,me);
    seteuid(getuid());
    me->set("actions", (: call_other, SKILL_D("kusang-bang"), "query_action" :) );
    weapon->set("use_apply_skill",1);
    weapon->set("apply/skill_type","stick");
    enhance=me->query_skill("kusang-bang",1);
    me->add_temp("apply/attack", enhance);  
    COMBAT_D->do_attack(me, target,weapon);
    weapon->set("use_apply_skill",weapon->query_temp("original/use_apply_skill"));
    weapon->set("apply/skill_type",weapon->query_temp("original/skill_type"));
    me->add_temp("apply/attack",-enhance);
    me->add_temp("apply/damage",-damage);
    me->reset_action();
    if ( (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0)) && !random(5) )  
       {str=target->name()+HIM"��"+me->name()+"����ڤ��ѧ"NOR+HIB"�����ˡ���"+HIM"�����ˣ�ʬ����ɫ�����ɲ����Ʊ�������";
         message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
	}
    me->add("force", -100);
/*        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
        }*/
  me->set_temp("three_end",time());
  return 1;
}

