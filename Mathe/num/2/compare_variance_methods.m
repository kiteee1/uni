## Copyright (C) 2024 roman
##
## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <https://www.gnu.org/licenses/>.

## -*- texinfo -*-
## @deftypefn {} {@var{retval} =} compare_variance_methods (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: roman <roman@DESKTOP-P8RI8NT>
## Created: 2024-10-27

function compare_variance_methods()
    true_mean = 1e5;
    true_variance = 1e-5;
    n_values = [10, 100, 1000, 10000, 100000, 1000000];

    errors_formula_1 = zeros(length(n_values), 1);
    errors_formula_2 = zeros(length(n_values), 1);

    for i = 1:length(n_values)
        n = n_values(i);

        data = true_mean + sqrt(true_variance) * randn(n, 1);

        mean_data = mean(data);
        variance_formula_1 = sum((data - mean_data).^2) / n;

        variance_formula_2 = mean(data.^2) - (mean(data))^2;

        errors_formula_1(i) = abs(variance_formula_1 - true_variance);
        errors_formula_2(i) = abs(variance_formula_2 - true_variance);
    end

    fprintf("Dataset Size (n) | Error Formula 1 | Error Formula 2\n");
    for i = 1:length(n_values)
        fprintf("%15d | %15.6f | %15.6f\n", n_values(i), errors_formula_1(i), errors_formula_2(i));
    end

    figure;
    hold on;
    plot(n_values, errors_formula_1, '-o', 'DisplayName', 'Error Formula 1');
    plot(n_values, errors_formula_2, '-x', 'DisplayName', 'Error Formula 2');
    set(gca, 'XScale', 'log');
    hold off;

    xlabel('Dataset Size (n)');
    ylabel('Absolute Deviation from True Variance');
    title('Deviation of Calculated Variance from True Variance');
    legend('show');
    grid on;
end
