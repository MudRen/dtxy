// perform.c
#include <skill.h>
#include "/cmds/std/valid_kill.h";

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object weapon, target;
        mapping smap, pmap, prepare;
        string martial, skill, perf;
string action,file,target_ob;
        seteuid(getuid());
        smap = me->query_skill_map();
        pmap = me->query_skill_prepare();
        if( me->is_busy() )
                return notify_fail("( ����һ��������û����ɣ�����ʩ���⹦��)\n");

        if( !arg ) return notify_fail("��Ҫ���⹦��ʲô��\n");
        if ( !wizardp(me) && environment(me)->query("no_fight")) 
                return notify_fail("���ﲻ��ʩ���⹦��\n");
	//if( me->query("anger")< 30 )
//		return notify_fail("��ŭ��������ʹ�����⹥��!\n");
        if( sscanf(arg, "%s on %s", perf, arg)==2 ) {
                target = present(arg, environment(me));
                if( !target ) target = present(arg, me);
                if( !target ) return notify_fail("����û�� " + arg + "��\n");

                if(!valid_kill(me,target)) return 0;

                if( userp(me) && userp(target) && 
                    target->query_temp("netdead") )
                   return notify_fail("�Է����ڶ����У����ܶ���ʩ���⹦��\n");

                arg=perf+" "+arg;
        } else if(sscanf(arg, "%s %s", perf, arg)==2 ) {
          //so can't use: perform vision id
          //but have to use: perform vision on id
          arg=perf;
        }
        if( sscanf(arg, "%s.%s", martial, arg)!=2 ) {
                if( weapon = me->query_temp("weapon") )
                        martial = weapon->query("skill_type");
                else if( weapon = me->query_temp("secondary_weapon") )
                       martial = weapon->query("skill_type");
                else if ( sizeof(pmap) == 0) martial = "unarmed";
                else if ( sizeof(pmap) == 1) martial = (keys(pmap))[0];
                else if ( sizeof(pmap) == 2) martial = (keys(pmap))[me->query_temp("action_flag")];
//else
  //                      martial = "unarmed";
        }
 else{
 if( martial == "axe" ||
     martial == "blade" ||
            martial == "dagger" ||
            martial == "fork" ||
            martial == "hammer" ||
            martial == "parry" ||
            martial == "unarmed" ||
            martial == "staff" ||
            martial == "sword" ||
            martial == "throwing" ||
            martial == "spear" ||
            martial == "whip" )
   return notify_fail("�����⹦����ָ���书���࣡\n");
 }
  //      if( weapon = me->query_temp("weapon") )
    //        martial = weapon->query("skill_type");
    //    else
      //      martial = "unarmed";


        if( stringp(skill = me->query_skill_mapped(martial)) ) {
notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");
                if( SKILL_D(skill)->perform_action(me, arg) ) {
                        if( random(120) < (int)me->query_skill(skill) )
                                me->improve_skill(skill, 1, 1);
                        return 1;
                } else if( SKILL_D(martial)->perform_action(me, arg) ) {
                        if( random(120) < (int)me->query_skill(martial, 1) )
                                me->improve_skill(martial, 1, 1);
                        return 1;
                }
else {
if( sscanf(arg, "%s %s", action, target_ob)==2 )
                            {
target = present(target_ob, environment(me));
if( !target )
                                  return notify_fail("����û�� " + target_ob + "��\n");
                            }
                            else
                            {
                                action = arg;
                            }

file = CLASS_D("fuqiperform/")+action;
if( !stringp(file) || file_size(file + ".c") <= 0 )
                            return 0;

return (int)call_other( file, "perform", me, target);
                       }
return 0;
        }
        return notify_fail("�������� enable ָ��ѡ����Ҫʹ�õ��⹦��\n");
}

int help (object me)
{
        write(@HELP
ָ���ʽ��perfrom [<�书����>.]<��ʽ����> [<ʩ�ö���>]

�������ѧ���⹦(ȭ�š�����������....)��һЩ����Ĺ�����ʽ����ʽ������
�����ָ����ʹ�ã���������� enable ָ��ָ����ʹ�õ��书����ָ���书��
��ʱ�����ֵ��⹦��ָ���ȭ�Ź���ʹ������ʱ���Ǳ��е��书��


���仰˵��ֻҪ�� enable �е��书��������ʽ�ģ������������ָ��ʹ�á�
HELP
        );
        return 1;
}

