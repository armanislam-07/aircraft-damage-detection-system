%% Written by Arman Islam (islam149@purdue.edu)

filename = 'Resistance-Log-2026-05-07T16-59.csv'; % Replace here with filename of test to analyze
data = readmatrix(filename);
timeinMS = data(:,1);
resistance = data(:, 2);
voltage = data(:, 3); % Currently no use 
current = data(:, 4); % Currently no use 
time = timeinMS / 1000; % Converts our time into seconds

%% TO TRUNCATE WHAT WE WANT TO DISPLAY
% i = find(time > VALUE_WE_WANT_TIME_TO_START)
% To truncate the beginning
% time = time(i:end)
% resistance = resistance(i:end)
%
% To truncate an end
% time = time(1:endValue)
% resistance = resistance(1:endValue)
%%%% We can also utilize MATLABS for the resistance too | For instance: I want to cut
%%%% out where the resistance is 0 since that is when we plugged the
%%%% battery out etc. 

% Figure that shows our resistance over time
figure(1)
plot(time, resistance,LineWidth=5) %Adjust depending on data size
xlabel('Time (s)')
ylabel('Resistance (Ohms)')
title('Resistance vs Time of UAV flight test')
