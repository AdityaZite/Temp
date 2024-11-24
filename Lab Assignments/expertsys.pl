% Define house problems based on symptoms
house_problem(leaky_roof) :- symptom(water_stains), symptom(damp_smell).
house_problem(clogged_sink) :- symptom(slow_draining), symptom(gurgling_sound).
house_problem(overheating) :- symptom(high_energy_bill), symptom(thermostat_issues).

% Predicate to ask yes/no questions about house symptoms
ask_symptom(Symptom) :-
    format('Is your house experiencing ~w? (yes/no) ', [Symptom]),
    read(Response),
    (Response == yes -> assert(symptom(Symptom));
    Response == no -> true;
    write('Please answer yes or no.'), nl, ask_symptom(Symptom)).

% Collect a limited number of symptoms based on user responses
get_symptoms :-
    ask_symptom(water_stains),
    ask_symptom(damp_smell),
    ask_symptom(slow_draining),
    ask_symptom(gurgling_sound).

% Predicate to predict house problem based on symptoms
predict_house_problem :-
    findall(Problem, house_problem(Problem), Problems),
    (member(leaky_roof, Problems) -> write('Possible house problem: Leaky Roof'), nl
    ; member(clogged_sink, Problems) -> write('Possible house problem: Blocked Sink'), nl
    ; member(overheating, Problems) -> write('Possible house problem: Overheating'), nl
    ; write('No matching house problem found for the provided symptoms.'), nl).

% To start the diagnosis
start :-
    get_symptoms,
    predict_house_problem.