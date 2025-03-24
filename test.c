#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#define FFT_LENGTH 4096   // 明确预期的数据量
#define MAX_LINE_LENGTH 256  // 假设每行不超过255字符
#define EPSILON 1e-6  // 允许的对称误差
#define TOLERANCE 5   // 允许的最大偏离中心索引数
#define Pi 3.1415926
/**
 * @brief 读取单列浮点数据到预分配数组
 * @param filename 文件名
 * @param buffer 预分配的浮点数组（长度需>=EXPECTED_ROWS）
 * @return 成功读取的数据量，错误返回-1
 */

int max(int a,int b)
{
    if(a>b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int min(int a,int b)
{
    if(a<b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

 float FFT_result[2048];
 float FFT_Phase[2048];

int read_float_column(const char* filename, float buffer[FFT_LENGTH/2]) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "错误：无法打开文件 %s (%s)\n", filename, strerror(errno));
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    int count = 0;
    char* endptr;

    while (fgets(line, sizeof(line), fp) && count < FFT_LENGTH/2) {
        // 去除换行和回车符
        line[strcspn(line, "\r\n")] = 0;

        // 跳过空行
        if (strlen(line) == 0) continue;

        // 转换为浮点数
        errno = 0;
        double value = strtod(line, &endptr);
        
        // 检查转换有效性
        if (endptr == line || errno != 0) {
            fprintf(stderr, "数据格式错误 @ 行 %d: %s\n", count+1, line);
            fclose(fp);
            return -1;
        }

        buffer[count++] = value;
    }

    fclose(fp);

    // 验证数据量
    if (count != FFT_LENGTH/2) {
        fprintf(stderr, "数据量不足：期望 %d 行，实际 %d 行\n", FFT_LENGTH/2, count);
        return -1;
    }

    return count;
}

int FindPeaksNumber(float arr[], int n)
{
    int count = 0;
    if((arr[0]>arr[1])&&(arr[0] > 30))
        count++;

    for(int i = 1; i < n - 1; i++)
    {
        if((arr[i] > arr[i-1])&&(arr[i]>arr[i+1])&&(arr[i]>30))
            count++;
    }

    if((arr[n-1]>30)&&(arr[n-1]>arr[n-2]))
        count++;
        
    return count; 
}
void main(void)
{
    FILE *fp;
    int nbrOfpeak;
    int nbrOfMainPeak;
    float max_amp_0 = 0;
    float max_amp_1 = 0;
    float min_amp;
    int max_freq_0 = 0;
    int max_freq_1 = 0;
    int max_0 = 0;
    int max_1 = 0;
    int sure0 = 0;
    int sure1 = 1;
    int sure2 = 0;
    float v_down_min;
    float v_down_max;
    float mean_delta_freq;
    float m_a;
    float F;
    float m_f;
    float delta_f;
    float R_c;
    float h;

    int ret = read_float_column("Data_ASK_6.log", FFT_result);

    nbrOfpeak = FindPeaksNumber(FFT_result, FFT_LENGTH/2);
    
    float PeakAmp[nbrOfpeak];
    int PeakFreq[nbrOfpeak];
	
	if (PeakAmp == NULL||PeakFreq == NULL)
		return;	

    int count = 0;
    if((FFT_result[0]>FFT_result[1])&&(FFT_result[0] > 30))
    {
        PeakAmp[count] = FFT_result[0];
        PeakFreq[count] = 0;
        count++;
    }
    for(int i = 1; i < FFT_LENGTH/2 - 1; i++)
    {
        if((FFT_result[i] > FFT_result[i-1])&&(FFT_result[i]>FFT_result[i+1])&&(FFT_result[i]>30))
        {
            PeakFreq[count] = i;
            PeakAmp[count] = FFT_result[i];
            count++;
        }
    }
    
    if((FFT_result[FFT_LENGTH/2-1]>30)&&(FFT_result[FFT_LENGTH/2-1]>FFT_result[FFT_LENGTH/2-2]))
    {
        PeakAmp[count] = FFT_result[FFT_LENGTH/2 - 1];
        PeakFreq[count] = FFT_LENGTH/2 - 1;
    }
    for(int i=0;i<nbrOfpeak;i++)
    {
        if(i==0)
        {
            min_amp = 1000;
        }
        min_amp = fmin(min_amp,PeakAmp[i]);
    }
    nbrOfMainPeak = min(3,FindPeaksNumber(PeakAmp,nbrOfpeak));
    count = 0;
    float MainPeakAmp[nbrOfMainPeak];
    int MainPeakFreq[nbrOfMainPeak];
    if((PeakAmp[0]>PeakAmp[1]) &&(PeakAmp[0]-min_amp)>55.0)
    {
        MainPeakAmp[count] = PeakAmp[0];
        MainPeakFreq[count] = PeakFreq[0];
        count++;
    }
    for(int i = 1; i < nbrOfpeak - 1; i++)
    {
        if((PeakAmp[i] > PeakAmp[i-1])&&(PeakAmp[i]>PeakAmp[i+1])&&(PeakAmp[i]-min_amp)>55.0)
        {
            MainPeakAmp[count] = PeakAmp[i];
            MainPeakFreq[count] = PeakFreq[i];
            count++;
        }
    }
    
    if((PeakAmp[nbrOfpeak-1]>PeakAmp[nbrOfpeak-2]) &&(PeakAmp[nbrOfpeak-1]-min_amp)>55.0)
    {
        MainPeakAmp[count] = PeakAmp[nbrOfpeak - 1];
        MainPeakFreq[count] = PeakFreq[nbrOfpeak - 1];
        count++;
    }
    nbrOfMainPeak = count;
    for(int i = 0; i < nbrOfpeak; i++)
    {
        printf("freq = %d\t", PeakFreq[i]);
        printf("amp = %f\n", PeakAmp[i]);
        if (PeakAmp[i] > max_amp_0) 
        {
            max_amp_1 = max_amp_0;
            max_freq_1 = max_freq_0;
            max_1 = max_0;
            max_amp_0 = PeakAmp[i];
            max_freq_0 = PeakFreq[i];
            max_0= i;
        } 
        else if (PeakAmp[i] < max_amp_0 && PeakAmp[i] > max_amp_1)
        {
            max_amp_1 = PeakAmp[i];
            max_freq_1 = PeakFreq[i];
            max_1 = i;
        }

    }

    float delta_freq[nbrOfpeak - 1];

    sure0 = 0;
    if(abs(max_0-max_1)==2 && PeakAmp[max(max_0,max_1)-1]/max_amp_0 <= 0.2)
    {
        sure0 = 1;  //判断双峰是否相邻
    }
    if(abs(max_0-max_1)==1 && (max_amp_0-max_amp_1)/max_amp_0 <= 0.2)
    {
        sure0 = 1;
    }
    for (int i = nbrOfpeak-1; i>0; i--)
    {
        delta_freq[nbrOfpeak-1 - i] = PeakFreq[i] - PeakFreq[i-1];
    }
    if(nbrOfMainPeak == 1)   //判断是否是单主峰
    {
        sure2 = 1;
        if(sure0 == 1)
        {
            sure2 = 0;
        }
    }
    else if(nbrOfMainPeak>1)
    {
        sure2 = 0;
    }
    for(int i = 1;i<nbrOfpeak-1;++i)  //判断相邻峰的频率之差是否相等
    {
			if(i == 1)	
			{
				sure1 = 1;
			}
			if(fabs(delta_freq[i] - delta_freq[i-1]) >= 2.0)
			{
				sure1 = 0;
                
				if(delta_freq[i]/2-delta_freq[i-1]<=1.5 && sure2 == 0)
				{
					sure1 = 1;
                    delta_freq[i] = delta_freq[i]/2;
				}
              
			}
    }

    for(int i = 0;i<nbrOfpeak - 1;i++ )
    {
        if(i == 0)
        {
            mean_delta_freq = 0;
        }
        mean_delta_freq += delta_freq[i];
    }

    mean_delta_freq /=  nbrOfpeak - 1;

    if(nbrOfpeak == 1)
    {
        printf("CW");
    }
    if(nbrOfpeak == 3)
    {
        printf("AM\n");
        F = (float)(PeakFreq[2] - PeakFreq[0])/2/FFT_LENGTH*400;
		m_a = (PeakAmp[1] - min(PeakAmp[0],PeakAmp[2]))/(PeakAmp[1] + min(PeakAmp[0],PeakAmp[2]));
        printf("F = %f\tm_a = %f\n", F ,m_a);
    }
    if(nbrOfpeak > 3)
    {
        if((max_amp_0 - max_amp_1)/max_amp_0 <= 0.2 && abs(max_freq_0 + max_freq_1 - FFT_LENGTH/2) <= 1 && sure0 == 1)
        {
            printf("2PSK\n");
			R_c = (float)abs(max_freq_1 - max_freq_0)/2/FFT_LENGTH*400;
            printf("R_c = %f\n", R_c);
        }
        else
        {
            if(abs(max_freq_0 - FFT_LENGTH/4) <= 1 && abs(PeakFreq[max_0-1]+PeakFreq[max_0+1]-FFT_LENGTH/2)<=1 && sure1 == 0 && sure2 == 1)
            {
				R_c = (float)(PeakFreq[max_0+1]-PeakFreq[max_0-1])/2/FFT_LENGTH*400;
                printf("2ASK\n");
                printf("R_c = %f\n", R_c);
            }
            else if(sure1 == 1 && sure0 == 0 && sure2 == 0 && mean_delta_freq > 55.0f)
            {
                printf("2FSK\n");
                R_c = mean_delta_freq/FFT_LENGTH*400;
			    h = fabs(MainPeakAmp[0] - MainPeakAmp[nbrOfMainPeak-1])/mean_delta_freq;
                printf("R_c  =%f\th = %f\n", R_c, h);
            }
            else
            {
                printf("FM\n");
                F = mean_delta_freq/FFT_LENGTH*400;
				m_f = (float)(PeakFreq[nbrOfpeak-1]-PeakFreq[0])/2/F/FFT_LENGTH*400-1;
				delta_f = F*m_f;
                printf("F = %f\tm_f = %f\tdelta_f = %f\n", F, m_f, delta_f);
            }
        }
    }
    

}

