#include <ansi.h>
inherit SSERVER;
string *where = ({"��","��","ǰ","��","��ǰ","���","��ǰ","�Һ�"});
int perform(object me, object target)
{
        object weapon;
        int skl,i,k;
        string msg;
        int cd = 10;
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ����˭��\n");
          if((me->query("family/family_name") != "��ɽ��")&&(!wizardp(me)))
                return notify_fail("�������ɽ���ӣ�����ʹ����ɽ����?\n");
        if(!me->is_fighting(target))
                return notify_fail("����û���ڴ�ܣ�\n");
        //if(target->is_busy())
        //        return notify_fail("�Է���æ�ţ���Ļ���Ҫ�����У�\n");
        if((int)me->query("max_force") < 1000 )
                return notify_fail("����ڹ�̫�\n");
        if((int)me->query("force") < 1800 )
                return notify_fail("����������㣡\n");
        if((int)me->query("sen") < 500 )
                return notify_fail("��ľ����㣬û����ʩ���⹦��\n");
	if((int)me->query_skill("taoism", 1) < 120
         ||(int)me->query_skill("spells", 1) < 120)
        	return notify_fail("��ķ����ȼ�����������ʹ����һ�У�\n");
        skl=(int)me->query_skill("mindsword", 1);
        if((int)me->query_skill("sword")<120
           || skl< 120)      
                  return notify_fail("��Ľ������𻹲�����ʹ����һ�л������ѣ�\n");
        if( me->query("lunhui_zhuanshi") > 4 )
		cd = 7;
        if(time()-me->query_temp("yjwd_end")<cd) return notify_fail("�����޵в����õ���ôƵ����\n");         
        me->set_temp("yjwd_end",time());
        //me->add("force",300);
  k=skl;
  skl/=50;
  if (skl>6) skl=6;
  //target->start_busy(random(skl));
  me->set("env/brief_message",1);
  target->set("env/brief_message",1);
  weapon = me->query_temp("weapon");
  message_vision(HIR"\nֻ��,$NĬ����ʦ������˫Ŀ���࣬ȫ���ʱϼ�Ⱪ�֣�����\n"NOR,me,target);
  message_vision(HIG"\n$N���һ����\n"NOR,me,weapon);
  message_vision(BLINK+HIR"\n\n\t\t������� �����޵�\n\n"NOR,me,weapon);
  message_vision(HIG"\n����$n"+HIG"ȽȽ�������С�����\n"NOR,me,weapon);
  for(i=1;i<=skl;i++)
        {
        me->add("force",-60);
        me->receive_damage("sen", 30);
        msg=weapon->name()+HIB"���ڿ��У�ͻȻ��"+HIR+where[random(sizeof(where))]+HIB+"������$n��\n";
        message_vision(HIB+msg+NOR,me,target);
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"),1);
        if(random(me->query("combat_exp"))>target->query("combat_exp")/3)
            { 
            msg="\n"+weapon->name(1)+HIW"ͻȻ�ַ��˻�������"HIG"��ȫ�����ܵĽǶ�"HIW"����$n��\n";
            message_vision(HIW+msg+NOR,me,target);         
            target->receive_wound("sen",k);
            target->receive_wound("kee",k);
            COMBAT_D->report_status(target,0);
            COMBAT_D->report_sen_status(target,0);
            }
        }
//if(random(3)) message_vision(HIG"\n$n"HIG"�ڿ��з���һȦ���ַɻص�$N���У�\n"NOR,me,weapon);        
//else {
     //weapon->move(environment(me));
     //message_vision("\n$n"HIR"�ڿ��з���һȦ��ͻȻб���ڵ��ϣ�\n"NOR,me,weapon); 
     message_vision(HIR"\n$N����һ�У�$n"HIR"�ڿ���ת���䣬׼ȷ���������$N���У�\n"NOR,me,weapon); 
//}
me->start_busy(2);
return 1;
 }
