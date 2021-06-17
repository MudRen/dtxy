inherit F_CLEAN_UP;
#include <ansi.h>

int main(object me, string arg)
{
        int skill_lvl, lvl=0;
        string skill;

        if(!arg || arg == "" || sscanf(arg, "%s %d", skill, lvl)!=2 &&
           sscanf(arg, "%s", skill)!=1)
                return notify_fail("��Ҫ�����趨��һ��ܣ�\n");
        skill_lvl = me->query_skill(skill,1);
    if( lvl < 1 )
        return notify_fail("���ܼ�����С��1,papaya��\n");
    if( skill_lvl > 200 )
        return notify_fail("��Ҳ���������ˣ��������ʱ�򣿲��У���\n");
    if( lvl == skill_lvl && lvl>0)
                return notify_fail("��������û�����������ڲ���������ȼ���\n");
        if( lvl > skill_lvl )
                return notify_fail("�������û��ô�ߣ�\n");
        if( !me->delete_skill(skill) )
                return notify_fail("�㻹��������ܡ�\n");
        write("��� " HIR+ to_chinese(skill) + NOR" �������̶������仯��\n");
        if( lvl > 0 ) me->set_skill(skill, lvl);
        return 1;
}

int help()
{
        write(@TEXT
ָ���ʽ��fangqi2 <��������> [Ҫ�������ļ���]

�����趨һ������ѧ���ļ��ܣ�ע��������˵�ġ���������ָ������ܴ�������
�������������趨��һ���ļ��𣬲�������200����skills�Ͳ��ܵ����ˡ�

��������ڷ�������ʱû�����뼶�𣬽�ȫ����������ܡ�

���ָ��ʹ�õĳ���ͨ���������趨һЩ����С�ġ��������������˵ĵļ��ܡ�

TEXT
        );
        return 1;
}
