int main(object me, string arg)
{
        mixed *ob;
        int i,j;
        string output;

        output = sprintf("%-20s %-6s %s\n", "����", "ID","���");
        if( arg && arg!="" )
        ob = objects( (: query_heart_beat :) );
        else
        ob = objects( (: query_heart_beat :) );

    j =sizeof(ob);
output += sprintf("�ܹ���%d������\n", j);
if(j > 1000) j=1000;
        for(i=0; i<j; i++) {
                        output += sprintf("%10s : %15s : %20s\n",ob[i]->query("name"),ob[i]->query("id"),file_name(ob[i]));
        }

        me->start_more(output);
        return 1;
}


int help()
{
        write(@LONG
ָ���ʽ��checkob

��ѯ������Ʒ��

LONG
        );
        return 1;
}
