// write by canoe
// ��ѯ����player״̬
#include <ansi.h>
int help(object me);
int main(object me, string name)
{       
        object ob; 
        mapping skl,lrn, map;
        string *sname, *mapped;
	int i,flag;
        if( !name) return help(me);
	seteuid(getuid());
	if(!ob=find_player(name))
        	{
        	flag=1;
        	ob = new(USER_OB);
        	ob->set("id", name);
        	if (!ob->restore()) return notify_fail("û�������ҡ�\n");
        	}
        write("\n"+HIY+ob->name(1)+NOR+"״̬���£����ɣ�"+HIY);
        write(ob->query("family/family_name")?ob->query("family/family_name"):"��ͨ����");
        write(NOR+"��ѧ��"+HIY+ob->query("combat_exp")+NOR+"\t���У�"+HIY+COMBAT_D->chinese_daoxing(ob->query("daoxing"))+NOR+"\n");
        write("������"+HIY+ob->query("max_force")+NOR+"\t������"+HIY+ob->query("max_mana")+NOR+"\t�������̣�"+HIY+FINGER_D->age_string((int)ob->query("mud_age"))+NOR+"\n");
        skl = ob->query_skills();
        if(!sizeof(skl))
                {
		write(ob->name(1)+ "Ŀǰ��û��ѧ���κμ��ܡ�\n");
		return 1;
	        }
        write( "Ŀǰ�����յļ������£�\n");
        sname  = sort_array( keys(skl), (: strcmp :) );
	map = ob->query_skill_map();
	if( mapp(map) ) mapped = values(map);
	if( !mapped ) mapped = ({});
	lrn = ob->query_learned();
	if( !mapp(lrn) ) lrn = ([]);
	for(i=0; i<sizeof(skl); i++)
		 {
		printf("%s%s%-40s" NOR " - %-10s %4d/%5d\n", 
		(lrn[sname[i]] >= (skl[sname[i]]+1) * (skl[sname[i]]+1)) ? HIM : "",
		(member_array(sname[i], mapped)==-1? "  ": HIR"��"NOR),
		to_chinese(sname[i]) + " (" + sname[i] + ")",
		SKILL_D(sname[i])->level_description(skl[sname[i]]),
		skl[sname[i]], (int)lrn[sname[i]],);
	        }
	write("\n");
        if (flag) destruct(ob);
        return 1;
}

int help(object me)
{
write(@HELP
ָ���ʽ��adcheck <id>
�쿴ĳ�����״̬�����������ߵġ�
HELP
	);
    return 1;
}
